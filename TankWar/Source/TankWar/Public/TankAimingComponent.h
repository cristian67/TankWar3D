// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankBarrel.h"
#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKWAR_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTankAimingComponent();

	//ApuntarHacia
	void AimAt(FVector HitLocation, float LaunchSpeed);

	//Llamar referencia del barrel
	void SetBarrelReference(UTankBarrel *BarrelToSet);

private:

	//LLAMAR A BARREL = CAÑON
	//UStaticMeshComponent *Barrel = nullptr;
	UTankBarrel *Barrel = nullptr;

	//ROTAR BARREL 
	void MoveBarrel(FVector AimVector);

};
