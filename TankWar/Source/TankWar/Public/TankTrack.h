// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"



class ASprungWheel;


/**
 *  Definir maxima fuerza de conduccion y mover el tanque
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class TANKWAR_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	//moviemiento en +1 y -1
	UFUNCTION(BlueprintCallable, Category = "Input")
		void SetThrottle(float Throttle);

	//fuerza de movimiento,  segun el principio de NEWTON ; fuerza = masa * aceleracion
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 400000;

private:
	UTankTrack();



	TArray< ASprungWheel *> GetWheels() const;

	

	void DriveTrack(float CurrentThrottle);

	

};