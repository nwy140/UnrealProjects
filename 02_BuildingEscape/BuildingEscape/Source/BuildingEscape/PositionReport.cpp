// Fill out your copyright notice in the Description page of Project Settings.

#include "PositionReport.h"
#include <GameFramework/Actor.h>

// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();

	FString ObjectName = GetOwner()->GetName(); //return FString	// you need to include header	Gameframework/Actor.h to access AActor class methods
													// since GetOwner is an AActor pointer to component memory address// instead of using (*GetOwner).methodname//we use GetOwner->methodname // to simplify deferencing pointer to access method

	UE_LOG(LogTemp, Warning, TEXT("Position report reporting for duty on %s!" ), *ObjectName); //Log for grey text,Warning for yellow text,Error for red text
																				//Goto developer tools and output log to view printing text
																					//dereferece object name to get its FString , or else you are getting its memory address		

	// ...
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

