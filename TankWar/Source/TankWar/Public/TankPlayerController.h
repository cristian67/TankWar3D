// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANKWAR_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public: 
	ATank *GetControllerTank() const;
	
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//Mover barrel, methodo para inicializar apuntar
	void AimTowardsCrosshair();
	//Varible, si golpea landscape
	bool GetSightRayHitLocation(FVector &HitLocation) const;

private:
	UPROPERTY(EditAnywhere)
		float CrosshairXLocation = 0.5f;
	UPROPERTY(EditAnywhere)
		float CrosshairYLocation = 0.333f;

	bool GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const;
};
