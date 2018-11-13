// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

class UTankTurret;
class UTankBarrel;
class TankAimingComponent;

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// No es necesario proteger punteros que se agregan al contructor. 
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

}
 

//REFERENCIA AL CAÑON
void ATank::SetBarrelReference(UTankBarrel *BarrelToSet) {
	
	TankAimingComponent->SetBarrelReference(BarrelToSet);
}

//REFERENCIA A LA TORRETA 
void ATank::SetTurretReference(UTankTurret *TurretToSet) {

	TankAimingComponent->SetTurretReference(TurretToSet);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); 
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation) {
	
	//LLAMAR A AIMCOMPONENT
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
	
}


