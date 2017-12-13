// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call SUper as we're replacing the functionality 

	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal(); //GetForwardActor gets local object forward red axis
	auto AIForwardIntention = MoveVelocity.GetSafeNormal(); //GetSafeNormal() gets normal of MoveVelocity without changing MoveVelocity
	//UE_LOG(LogTemp, Warning, TEXT("%s vectoring to %s"), *TankName ,  )

	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveFoward(ForwardThrow);

	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendMoveRight(RightThrow);
}

void UTankMovementComponent::IntendMoveFoward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }

	//auto Time = GetWorld()->GetTimeSeconds();
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

	//TODO Prevent double speed due to dual control	
}

void UTankMovementComponent::IntendMoveRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }

	//auto Time = GetWorld()->GetTimeSeconds();
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

	//TODO Prevent double speed due to dual control	
}


