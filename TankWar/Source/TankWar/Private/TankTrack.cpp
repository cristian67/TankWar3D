// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle) {

	/*auto name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s movimiento track: %f"), *name, Throttle);*/

	//Adjustar valores
	auto ForceApplicada = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplicada, ForceLocation);
}



