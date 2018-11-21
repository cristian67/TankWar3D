// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialise(UTankTrack *LeftTrackToSet, UTankTrack *RightTrackToSet) {
	
	//Validacion
	if (!LeftTrackToSet || !RightTrackToSet) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw) {

	//Validacion
	if (!LeftTrack || !RightTrack) { return; }

	//LLamar metodo de TanTrack
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

	//Fix Velocidad
}

void UTankMovementComponent::IntendTurnRight(float Throw) {
	
	//Validacion
	if (!LeftTrack || !RightTrack) { return; }
	//LLamar metodo de TanTrack
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

	//Fix Velocidad
}