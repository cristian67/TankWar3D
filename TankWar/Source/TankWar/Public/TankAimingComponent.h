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
	Locked,
	OutOfAmmo
};


//Clases
class UTankBarrel;
class UTankTurret;
class AProjectil;


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKWAR_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialise(UTankBarrel *BarrelToSet, UTankTurret *TurretToSet);

	//ApuntarHacia
	void AimAt(FVector HitLocation);

	EFiringState GetFiringState() const;

	//Categoria Funcion: Disparar (TANK)
	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();

	UFUNCTION(BlueprintCallable, Category = "Firing") 
	int32 GetRoundsLeft() const ;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState FiringState = EFiringState::Reloading;


private:
	// Sets default values for this component's properties
	UTankAimingComponent();


	virtual void BeginPlay() override;

	//CADA FRAME Reload
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	
	//CAÑON
	UTankBarrel *Barrel = nullptr;
	//TORRETA
	UTankTurret *Turret = nullptr;
	//Para la condicion
	double LastFireTime = 0;
	

	bool IsBarrelMoving();
	
	//Funcion: ROTAR BARREL 
	void MoveBarrel(FVector AimDirection);

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectil> ProjectileBlueprint;

	//Categorias: 
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		int32 RoundsLeft = 3;


	FVector AimDirection;

	
};
