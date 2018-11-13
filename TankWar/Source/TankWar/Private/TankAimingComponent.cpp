// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"

class UTankTurret;
class UTankBarrel;

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

//Referencia al CAÑON
void UTankAimingComponent::SetBarrelReference(UTankBarrel *BarrelToSet) {

	if (!BarrelToSet) { return; }
	Barrel = BarrelToSet; 
}

//Referencia a TORRETA
void UTankAimingComponent::SetTurretReference(UTankTurret *TurretToSet) {

	if (!TurretToSet) { return; }
	Turret = TurretToSet;
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {

	/*auto OurTankName = GetOwner()->GetName();
	auto BarrelLocation = Barrel->GetComponentLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s aiming At : %s  From  %s "  ), *OurTankName, *HitLocation.ToString(), *BarrelLocation);*/

	if (!Barrel) { return; }

	FVector OutLaunchVelocity;
	FVector StarLocation = Barrel->GetSocketLocation(FName("Projectil"));
	
	//CALCULAR EL OutLaunchVelocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StarLocation,
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
		/*auto TankName = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%s el  esta Disparando hacia %s "), *TankName, *AimDirection.ToString());*/
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found"), Time);
	}
	else {
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: No aim solve found"), Time);
	}
	
}

void UTankAimingComponent::MoveBarrel(FVector AimVector) {

	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimVector.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;

	//Deltarotation lo mueve con el movimiento de la camara
	Barrel->Elevate(DeltaRotator.Pitch); 

}

