// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


//Color
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};


//Clases
class UTankBarrel;
class UTankTurret;


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

protected:
	//Color Aim
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState FiringState = EFiringState::Aiming;


private:

	//CAÑON
	UTankBarrel *Barrel = nullptr;
	//TORRETA
	UTankTurret *Turret = nullptr;

	//ROTAR BARREL 
	void MoveBarrel(FVector AimDirection);

};
