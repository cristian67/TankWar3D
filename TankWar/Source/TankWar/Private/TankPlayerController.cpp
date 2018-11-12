// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {

	Super::BeginPlay();


	auto ControlledTank = GetControllerTank();
	if (!ControlledTank) {

		UE_LOG(LogTemp, Warning, TEXT("No se cuenta con el objeto tank, adjunte un objeto tanque"));
	} 
	else {
		UE_LOG(LogTemp, Warning, TEXT("playerControllerTank ready to play, tiene el objeto: %s "), *(ControlledTank->GetName() ));
	}

}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}


ATank * ATankPlayerController::GetControllerTank() const { 

	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {
	//verificar si tiene el controlador
	if (!GetControllerTank()) {return;}

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) {
		//llamar clase tank metodo AimAT
		GetControllerTank()->AimAt(HitLocation);
	}
	 
}

//Get world location si la linetrace esta a travez del crosshair
bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const {

	//Find the crooshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	//UE_LOG(LogTemp, Warning, TEXT("LOCATION Screen: %s"), *ScreenLocation.ToString());

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
		){
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