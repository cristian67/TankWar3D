// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
//SE AGREGO:  meta = (BlueprintSpawnableComponent) para que aparezca en blueprint
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("collision"))
class TANKWAR_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public: 
	// -1 es el maxdownward speed y +1 es maximo up movimiento
	void Elevate(float RelativeSpeed);
	
private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreesPerSecond = 20;
	
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevationPerSecond = 30;

	UPROPERTY(EditAnywhere, Category = Setup)
		float MinDegreesPerSecond = 0;
	
};
