// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
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


