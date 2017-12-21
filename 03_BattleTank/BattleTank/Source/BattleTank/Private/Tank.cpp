// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

#include "Engine/World.h" 
// Sets default values
ATank::ATank()
{
	// Set this pawn to		 call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); //Need for BP to run! //if you don't call super , Blueprints will  not call the entire BeginPlay method

}




