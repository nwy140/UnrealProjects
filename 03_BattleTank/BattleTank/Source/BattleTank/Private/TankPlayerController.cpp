// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

#include "Engine/World.h"


ATank* ATankPlayerController::GetControlledTank() const

{

	return   Cast<ATank>(GetPawn());  // casting allows you to access members (methods and attributes) of ATank Class

}



void ATankPlayerController::BeginPlay()

{

	Super::BeginPlay(); // makes sure BeginPlay on super class is called

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank) {

		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possesing a tank"));

	}

	else {

		UE_LOG(LogTemp, Warning, TEXT("PlayerController possesing: %s"), *(ControlledTank->GetName()));

	}



}

void ATankPlayerController::Tick(float deltatime)

{

	Super::Tick(deltatime);

	AimTowardsCrosshair();

}



void ATankPlayerController::AimTowardsCrosshair()

{
	if (!GetControlledTank()) { return; }
	FVector HitLocation; //OUT parameter

	if (GetSightRayHitLocation(HitLocation)) { //Has "side-effect" , is going to line trace
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());

		//if hits the lanscape

		// TODO: Tell controlledtank to aim at this point
	}
}

// GetWorldLocation of linetrace through crosshair	 , true if hit linescape		
bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation) const
{
#pragma region Find crosshair position
	// Find the crosshair position

	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX*CrossHairXLocation, ViewportSizeY* CrossHairYLocation); /// auto is a new C++11 type that automatically sets the correct class type for you
	//UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString())
#pragma endregion

	// "De-project" the screen position of the crosshair to a world direction
		// Line-trace alog that look direction, and see what we hit (up to max range)
		OutHitLocation = FVector(1, 0, 1);
	return true;
}
