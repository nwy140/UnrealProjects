// Fill out your copyright notice in the Description page of Project Settings.



#include "TankPlayerController.h"



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



	// GetWorldLocation if linetrace through crosshair			

	//if hits the lanscape

	// tell controlledtank to aim at this point

}