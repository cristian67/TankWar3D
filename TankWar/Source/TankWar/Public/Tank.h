// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "TankAimingComponent.h" 
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class TankAimingComponent;


UCLASS()
class TANKWAR_API ATank : public APawn
{
	GENERATED_BODY()

public:
	
	// CAÑON
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelReference(UTankBarrel *BarrelToSet);

	//TORRETA
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretReference(UTankTurret *TurretToSet);

	void AimAt(FVector HitLocation);

	//Disparar
	UFUNCTION(BlueprintCallable, Category = Firing)
		void Fire();

protected:
	//Componente Aiming
	UTankAimingComponent *TankAimingComponent = nullptr; 


private:
	// Sets default values for this pawn's properties
	ATank();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 10000; //metros por segundo

};
