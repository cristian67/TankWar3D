// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankWar.h"
#include "Kismet/GameplayStatics.h"
#include "TankTurret.h"
#include "TankBarrel.h"




// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel *BarrelToSet, UTankTurret *TurretToSet) {

	Barrel = BarrelToSet;
	Turret = TurretToSet;
}




void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {


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
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
		auto Time = GetWorld()->GetTimeSeconds();
	}/*
	else {
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: No encontro punteria, bug"), Time);
	}
	*/
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection) {

	if (!Barrel) { return; }
	if (!Turret) { return; }

	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;

	//Deltarotation lo mueve con el movimiento de la camara
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}

