// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h" 



float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth; //Cast them to a float to use them as decimal points as percentages 
}
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

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp<int32>(DamagePoints, 0, CurrentHealth); //avoid comparing floats to 0, so use int32, floats are never accurately equals to 0
	
	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0) {
		OnDeath.Broadcast();
	}
	//UE_LOG(LogTemp,Warning,TEXT("DamageAmount== %f , DamageToApply = %i"),DamageAmount,DamageToApply) //putting int in %f will return 0, you must specifically put int in %i
	return DamageToApply;
}




