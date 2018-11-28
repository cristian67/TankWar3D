// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankWar.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"



void ATankAIController::BeginPlay() {

	Super::BeginPlay();
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//Castear player a tipo de objeto Tank
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	//Obtiene la referencia propia (enemigoAI)
	auto ControlledTank = GetPawn() ;

	if (!ensure(PlayerTank && ControlledTank)) { return; } 
	
	//mover hasta el player
	MoveToActor(PlayerTank, AcceptRadius);

	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

	//apuntar al jugador
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	//disparo listo
	AimingComponent->Fire();
	
}




