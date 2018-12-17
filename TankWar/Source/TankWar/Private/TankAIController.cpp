// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankWar.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h"



void ATankAIController::BeginPlay() {

	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn * InPawn) {

	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PosesionTank = Cast<ATank>(InPawn);
		
		if (!PosesionTank) { return; }

		//subscribir el metodo local del tanque (dead event)
		PosesionTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossedTankDeath);
	}
}
 
void ATankAIController::OnPossedTankDeath() {

	if (!GetPawn()) { return; }

	GetPawn()->DetachFromControllerPendingDestroy(); 

}


// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//Castear player a tipo de objeto Tank
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	//Obtiene la referencia propia (enemigoAI)
	auto ControlledTank = GetPawn() ;

	if (!(PlayerTank && ControlledTank)) { return; } 
	
	//mover hasta el player
	MoveToActor(PlayerTank, AcceptRadius);

	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

	//apuntar al jugador
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	//disparo listo
	if (AimingComponent->GetFiringState() == EFiringState::Locked) {
		AimingComponent->Fire();
	}
}




