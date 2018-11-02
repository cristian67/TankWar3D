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


ATank * ATankPlayerController::GetControllerTank() const {

	return Cast<ATank>(GetPawn());
}

