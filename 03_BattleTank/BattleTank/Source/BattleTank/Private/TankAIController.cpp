// Fill out your copyright notice in the Description page of Project Settings.



#include "TankAIController.h"

#include "GameFramework/Pawn.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"

//Depends on MovementComponent via AI pathfinding

//Tank BP 's AIClass has been set this TankAiController class, so any tank spawned that is not possesed by player will use this class


void ATankAIController::BeginPlay()

{

	Super::BeginPlay();
}


void ATankAIController::Tick(float deltatime)
{
	Super::Tick(deltatime);
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }
	//Move Towards Player
	MoveToActor(PlayerTank, AcceptanceRadius); //TODO Check radius is in centimetres

	//Aim at Player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	// Use FindComponentByClass, Don't use GetComponentByClass

	//ControlledTank->Fire //TODO: Fix Firing

}

