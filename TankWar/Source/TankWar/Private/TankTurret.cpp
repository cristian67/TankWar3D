// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

// Funcion con Yaw
void UTankTurret::Rotate(float RelativeSpeed) {

	 
	//Dar maxima rotacion y el frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0, Rotation, 0));


}

