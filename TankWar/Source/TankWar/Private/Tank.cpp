// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankWar.h"
#include "Engine/World.h"
#include "Projectil.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h" 


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// No es necesario proteger punteros que se agregan al contructor. 
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));

}
 


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); 

	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();

}



void ATank::AimAt(FVector HitLocation) {
	
	if (!TankAimingComponent) { return; }

	//LLAMAR A AIMCOMPONENT
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
	
}

//REFERENCIA A LA TORRETA 
void ATank::Fire() {

	//Reload
	bool isReload = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeSeconds;
		
	auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("%f: tank fires "), Time);


	if (Barrel && isReload) {

		//Spawnear Projectil
		auto Projectile = GetWorld()->SpawnActor<AProjectil>(
			Projectile_BP,
			Barrel->GetSocketLocation(FName("Projectil")),
			Barrel->GetSocketRotation(FName("Projectil"))
			);

		//Velocidad del projectil lanzado
		Projectile->LanzarProjectil(LaunchSpeed);

		//Re-ajustar el time para la recarga
		LastFireTime = FPlatformTime::Seconds();
	}
}


