// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision")) //show up in custom components blueprint to be added to mesh in viewport
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Turn(float RelativeSpeed);
private:
	float MaxDegreesPerSecond = 5;
	//float MaxTurnDegrees = 360;
	//float MinTurnDegrees = 0;
	
	
};
