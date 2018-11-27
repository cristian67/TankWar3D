// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"


class ATank;
class UTankAimingComponent;

/**
 *	
 */
UCLASS()
class TANKWAR_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()


protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
		ATank *GetControllerTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent *AimToSet);

private:
	
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//Mover barrel, methodo para inicializar apuntar
	void AimTowardsCrosshair();
	//Varible, si golpea landscape
	bool GetSightRayHitLocation(FVector &HitLocation) const;

	UPROPERTY(EditAnywhere)
		float CrosshairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
		float CrosshairYLocation = 0.3333;
	UPROPERTY(EditAnywhere)
		float LineTranceRange = 1000000000; 

	bool GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const;
	bool GetLookVectorHit(FVector LookDirection, FVector &HitLocation) const;
};
