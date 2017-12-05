// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"
void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Move the barrel
	// Given a max elevation speed and the frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange; //relative means change difference 
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	//Clamp limits values of a variable between a min and max value, syntax is FMath::Clamp because it is a static method
	SetRelativeRotation(FRotator(Elevation, 0, 0)); //if has no hitresult, rotation might go back to 0

}


