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
	

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialise(UTankBarrel *BarrelToSet, UTankTurret *TurretToSet);


	//ApuntarHacia
	void AimAt(FVector HitLocation, float LaunchSpeed);


protected:
	//Color Aim
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState FiringState = EFiringState::Aiming;


private:
	// Sets default values for this component's properties
	UTankAimingComponent();
	//CAÑON
	UTankBarrel *Barrel = nullptr;
	//TORRETA
	UTankTurret *Turret = nullptr;

	//ROTAR BARREL 
	void MoveBarrel(FVector AimDirection);

};
