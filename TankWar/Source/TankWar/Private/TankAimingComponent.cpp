// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankWar.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "Projectil.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called every frame
void UTankAimingComponent::BeginPlay()
{
	LastFireTime = FPlatformTime::Seconds();

}

//INICIALIZAR PUNTEROS
void UTankAimingComponent::Initialise(UTankBarrel *BarrelToSet, UTankTurret *TurretToSet) {

	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {

	if ( RoundsLeft <= 0) 
	{
		FiringState = EFiringState::OutOfAmmo;	
	}

	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01); // vectors are equal
}



//FUNCION APUNTAR
void UTankAimingComponent::AimAt(FVector HitLocation) {


	if (!Barrel) { return; }
	if (!Turret) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectil"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bHaveAimSolution) {
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
		auto Time = GetWorld()->GetTimeSeconds();
	}
}

//FUNCION MOVER CAÑON
void UTankAimingComponent::MoveBarrel(FVector AimDirection) {

	if (!Barrel) { return; }
	if (!Turret) { return; }

	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;

	//Deltarotation lo mueve con el movimiento de la camara
	Barrel->Elevate(DeltaRotator.Pitch);
	if (FMath::Abs(DeltaRotator.Yaw) < 180) {
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else {
	
		Turret->Rotate(-DeltaRotator.Yaw);

	}
}


//FUNCION DISPARAR
void UTankAimingComponent::Fire() {
	
	if (FiringState != EFiringState::Reloading || FiringState == EFiringState::Aiming)
	{

		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		
		//Spawnear Projectil
		auto Projectile = GetWorld()->SpawnActor<AProjectil>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectil")),
			Barrel->GetSocketRotation(FName("Projectil"))
			);

		//Velocidad del projectil lanzado
		Projectile->LanzarProjectil(LaunchSpeed);

		//Re-ajustar el time par a la recarga
		LastFireTime = FPlatformTime::Seconds();
		RoundsLeft--;
	}
}

EFiringState UTankAimingComponent::GetFiringState() const {

	return FiringState;
}

int UTankAimingComponent::GetRoundsLeft() const {
	
	return RoundsLeft;
}