// Fill out your copyright notice in the Description page of Project Settings.



#pragma once



#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**

*

*/

//Forward declaration
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController

{

	GENERATED_BODY()

private:

	void BeginPlay() override;
	virtual void Tick(float deltatime) override;

	//How close can the AI tank gets to the player
	float AcceptanceRadius =3000;


};
	











/* 
ATank* GetAIControlledTank() const;



	ATank* GetPlayerTank() const;
*/
