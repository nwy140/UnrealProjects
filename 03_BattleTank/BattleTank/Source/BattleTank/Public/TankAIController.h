// Fill out your copyright notice in the Description page of Project Settings.



#pragma once



#include "CoreMinimal.h"

#include "AIController.h"


#include "TankAIController.generated.h"

/**

*

*/

//Forward declaration
class ATank;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController

{

	GENERATED_BODY()

private:

	void BeginPlay() override;
	virtual void Tick(float deltatime) override;


	ATank* GetAIControlledTank() const;



	ATank* GetPlayerTank() const;



};