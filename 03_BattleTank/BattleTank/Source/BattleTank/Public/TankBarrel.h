// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */

UCLASS(meta = (BlueprintSpawnableComponent) , hidecategories = ("Collision")) //This makes TankBarrel class show up as  custom component in  blueprint // Hide Categories hide Collision in Blueprint TankBarrel custom component
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 ix max downward movement , +1 is max up movement
	void Elevate(float RelativeSpeed);
private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 10; //5

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegrees = 40;
	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationDegrees = 0; 
	
};
