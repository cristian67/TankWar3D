// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "TankTurret.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h" 
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"



UCLASS()
class TANKWAR_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AimAt(FVector HitLocation);
	
	// CAÑON
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelReference(UTankBarrel *BarrelToSet);

	//TORRETA
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretReference(UTankTurret *TurretToSet);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override; 

	//Componente Aiming
	UTankAimingComponent *TankAimingComponent = nullptr; 


private:
	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 8000; //metros por segundo

};
