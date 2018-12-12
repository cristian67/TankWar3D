// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankWar.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h"


class Tank;

void ATankPlayerController::BeginPlay() {

	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::SetPawn(APawn * InPawn) {

	Super::SetPawn(InPawn);
	if (InPawn)
	{ 
		auto PosesionTank = Cast<ATank>(InPawn);

		if (!ensure(PosesionTank)) { return; }

		//subscribir el metodo local del tanque (dead event)
		PosesionTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossedTankDeath);
	}
}

void ATankPlayerController::OnPossedTankDeath() {

	StartSpectatingOnly();
}


// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}


//Punteria
void ATankPlayerController::AimTowardsCrosshair() {
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation;
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	if (bGotHitLocation) {
		//llamar clase tank metodo AimAT
		AimingComponent->AimAt(HitLocation);
	}
	 
}

//Get world location si la linetrace esta a travez del crosshair
bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const {

	//Find the crooshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	

	//Actualizar posicion del puntero(crosshair)
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		//linea de trazo y rango maximo de golpe
		GetLookVectorHit(LookDirection, HitLocation);
	}

	return true;
}

bool ATankPlayerController::GetLookVectorHit(FVector LookDirection, FVector &HitLocation) const {
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTranceRange);
	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
	
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const {

	FVector CamaraWorldLocation; //Descartado
	//DeprojectScreenPostitionToWorld es bool, y da valor a Camara y World
	return DeprojectScreenPositionToWorld( 
		ScreenLocation.X,
		ScreenLocation.Y, 
		CamaraWorldLocation, 
		LookDirection
		);
}