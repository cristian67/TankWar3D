// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "TankAimingComponent.h" 
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"



class AProjectil;
class UTankBarrel;
class TankAimingComponent;



UCLASS()
class TANKWAR_API ATank : public APawn
{
	GENERATED_BODY()

public:
	
	void AimAt(FVector HitLocation);

	//Disparar
	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();

protected:
	//Componente Aiming
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent *TankAimingComponent = nullptr; 




private:
	// Sets default values for this pawn's properties
	ATank();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Firing")
		float LaunchSpeed = 10000; //metros por segundo


	UPROPERTY(EditAnywhere, Category = "	Setup")
		TSubclassOf<AProjectil> Projectile_BP;   //metros por segundo

	//Local barrel
	UTankBarrel *Barrel = nullptr;

	//Recargar disparo
	float ReloadTimeSeconds = 5.0;

	//Para la condicion
	double LastFireTime = 0;
};
