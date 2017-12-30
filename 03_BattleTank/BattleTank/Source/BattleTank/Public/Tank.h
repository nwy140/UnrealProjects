// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()
protected:
	
	
public:
	// Sets default values for this pawn's properties
	ATank();
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	//Called by the negine when actor damage is dealt
private:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly,Category="Setup")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category="Health")
	int32 CurrentHealth = StartingHealth;



};
