// Fill out your copyright notice in the Description page of Project Settings.

/*
* TankTrack is used to set maximum driving force, and to apply forces to the tank
*/
#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{

	//TODO: Clamp Throttle
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot =Cast<UPrimitiveComponent> (GetOwner()->GetRootComponent()); //GetOwner gets Tank_Bp, GetRootComponent Get Tank Mesh but it gets a scene component which you can't add force to it, so you have to cast it down to PrimitiveComponent
	TankRoot->AddForceAtLocation(ForceApplied,ForceLocation);
}



