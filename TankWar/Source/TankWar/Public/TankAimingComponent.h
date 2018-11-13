// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankTurret.h"
#include "TankBarrel.h"
#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"



UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKWAR_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTankAimingComponent();

	//ApuntarHacia
	void AimAt(FVector HitLocation, float LaunchSpeed);

	//Llamar referencia del CAÑON
	void SetBarrelReference(UTankBarrel *BarrelToSet);

	//Llamar referencia de la TORRETA
	void SetTurretReference(UTankTurret *TurretToSet);

private:

	//LLAMAR A BARREL = CAÑON
	//UStaticMeshComponent *Barrel = nullptr;
	
	//CAÑON
	UTankBarrel *Barrel = nullptr;

	//TORRETA
	UTankTurret *Turret = nullptr;


	//ROTAR BARREL 
	void MoveBarrel(FVector AimVector);

};
