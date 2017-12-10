// Fill out your copyright notice in the Description page of Project Settings.



#include "TankAIController.h"

#include "GameFramework/Pawn.h"
#include "Components/PrimitiveComponent.h"
#include "Tank.h"
#include "Engine/World.h"

//Tank BP 's AIClass has been set this TankAiController class, so any tank spawned that is not possesed by player will use this class



void ATankAIController::BeginPlay()

{

	Super::BeginPlay();

	//auto AIControlledTank = GetAIControlledTank();

	/*auto PlayerTank = GetPlayerTank();

	if (!PlayerTank) {

		UE_LOG(LogTemp, Warning, TEXT("AIController can't find player tank"))

	}

	else {

		UE_LOG(LogTemp, Warning, TEXT("AIController found player: %s"), *(PlayerTank->GetName())) // Do not use getowner, because this class is not placed as a component for an object , so GetOwner points to null which causes a crash

	}																									//use GetPawn instead or use GetAiControlledTank which calls Cast  
	*/
}


void ATankAIController::Tick(float deltatime)
{
	Super::Tick(deltatime);
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (PlayerTank) { // always check for null
		
		//Move Towards Player
			
		//Aim at Player
	ControlledTank->AimAt(PlayerTank->GetActorLocation() );
									// Use FindComponentByClass, Don't use GetComponentByClass
		//TODO : Fire if ready , don't fire every frame
	ControlledTank->Fire();

	}
}

/*
ATank* ATankAIController::GetAIControlledTank() const

{

	return Cast<ATank>(GetPawn());

}



ATank* ATankAIController::GetPlayerTank() const

{

	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PlayerPawn) { return nullptr; }

	return Cast<ATank>(PlayerPawn);

}
*/  