// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"



void UTankBarrel::Elevate(float RelativeSpeed) {

	/*auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("time %f with elevate actived %f"), Time, RelativeSpeed);*/
	
	//Dar maxima elevacion y el frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds; 
	auto NewElevation = RelativeRotation.Pitch + ElevationChange;  
	//Ajustar con clamp()
	auto Elevation = FMath::Clamp<float>(NewElevation, MinElevation, MaxElevation);


	SetRelativeRotation(FRotator(Elevation, 0, 0));



} 
 