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

	//Categoria Funcion: Disparar (TANK)
	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();

protected:
	//Categoria: Color Aim
	UPROPERTY(BlueprintReadOnly, Category = "St  ate")
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
	//Recargar disparo
	float ReloadTimeSeconds = 5.0;
	//Para la condicion
	double LastFireTime = 0;
	
	
	//Funcion: ROTAR BARREL 
	void MoveBarrel(FVector AimDirection);

	//Categorias: 
	UPROPERTY(EditAnywhere, Category = "Firing")
		float LaunchSpeed = 10000; //metros por segundo
	
	UPROPERTY(EditAnywhere, Category = "Setup")
		TSubclassOf<AProjectil> Projectile_BP;   //metros por segundo



};
