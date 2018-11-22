// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankWar.h"
#include "Tank.h"
#include "Engine/World.h"



void ATankAIController::BeginPlay() {

	Super::BeginPlay();
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//Castear player a tipo de objeto Tank
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	//Obtiene la referencia propia (enemigoAI)
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (PlayerTank) {
		
		//mover hasta el player
		MoveToActor(PlayerTank, AcceptRadius);

		//apuntar al jugador
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		//disparo listo
		ControlledTank->Fire();
	}
}




