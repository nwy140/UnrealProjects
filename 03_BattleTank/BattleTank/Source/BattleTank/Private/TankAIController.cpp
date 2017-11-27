// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "GameFramework/Pawn.h"
//Tank BP 's AIClass has been set this TankAiController class, so any tank spawned that is not possesed by player will use this class
ATank* ATankAIController::GetAIControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto AIControlledTank = GetAIControlledTank();
	if (!AIControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController not possesing a tank")	)
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AIController possesing %s"), *(AIControlledTank->GetName()) ) // Do not use getowner, because this class is not placed as a component for an object , so GetOwner points to null which causes a crash
	}																									//use GetPawn instead or use GetAiControlledTank which calls Cast  
}

