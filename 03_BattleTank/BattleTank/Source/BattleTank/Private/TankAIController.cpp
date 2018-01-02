// Fill out your copyright notice in the Description page of Project Settings.



#include "TankAIController.h"

#include "GameFramework/Pawn.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h" // So we can implement OnDeath

//Depends on MovementComponent via AI pathfinding

//Tank BP 's AIClass has been set this TankAiController class, so any tank spawned that is not possesed by player will use this class


void ATankAIController::BeginPlay()

{

	Super::BeginPlay();
}


void ATankAIController::SetPawn(APawn * InPawn) //We use and override SetPawn because constructor is too early, and begin play might not be called
{
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto PossesedTank = Cast<ATank>(InPawn);
		if (!ensure(PossesedTank)) { return; }

		//Subscribe our local method to the tank's death event
		PossesedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);

	}
}

void ATankAIController::OnPossessedTankDeath()
{
	if (!ensure(GetPawn())) { return; } //TODO remove if okay
	GetPawn()->DetachFromControllerPendingDestroy();

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

	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire();
	}
}

