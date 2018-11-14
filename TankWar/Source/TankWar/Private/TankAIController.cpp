// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankWar.h"
#include "Tank.h"



void ATankAIController::BeginPlay() {

	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank) {

		UE_LOG(LogTemp, Warning, TEXT("No se cuenta con el PlayerTank, adjunte un objeto tanque"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("playerControllerTankAI encontro al jugador: %s "), *(PlayerTank->GetName()));
	}

}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank()) {
		

		//mover hasta el player

		//apuntar al jugador
		GetControllerTankAI()->AimAt(GetPlayerTank()->GetActorLocation());

		//disparo listo
	}
}

//Obtiene la referencia propia (enemigoAI)
ATank * ATankAIController::GetControllerTankAI() const {
	return Cast<ATank>(GetPawn());
}

//Obtiene la referencia del jugador
ATank * ATankAIController::GetPlayerTank() const {
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn){return nullptr;}
	return Cast<ATank>(PlayerPawn);
}

