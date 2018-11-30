// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialise(UTankTrack *LeftTrackToSet, UTankTrack *RightTrackToSet) {
	
	//Validacion
	if (!LeftTrackToSet || !RightTrackToSet) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}



 void UTankMovementComponent::RequestDirectMove(const FVector &MoveVelocity, bool bForceMaxSpeed) {

	 auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	 auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	 //la magia pa q se mueva usando coseno con funcion dotproduct
	 auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	 IntendMoveForward(ForwardThrow);

	 //uso del seno para rotar
	 auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;	
	 IntendTurnRight(RightThrow);
}


 void UTankMovementComponent::IntendMoveForward(float Throw) {

	 //Validacion
	 if (!ensure(LeftTrack || RightTrack)) { return; }

	 //LLamar metodo de TanTrack
	 LeftTrack->SetThrottle(Throw);
	 RightTrack->SetThrottle(Throw);

 }


void UTankMovementComponent::IntendTurnRight(float Throw) {
	
	//Validacion
	if (!ensure(LeftTrack || RightTrack)) { return; }
	//LLamar metodo de TanTrack
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

}