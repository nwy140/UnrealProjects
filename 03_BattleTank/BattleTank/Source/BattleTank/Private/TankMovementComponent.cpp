// CopyRight SilentWolfStudios SDN BHD

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


