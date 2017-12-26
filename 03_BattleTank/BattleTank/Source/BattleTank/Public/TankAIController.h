// Fill out your copyright notice in the Description page of Project Settings.



#pragma once



#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**

*

*/

//Forward declaration

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController

{

	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup") //Consider EditDefaultsOnly //must be protected or else BP's edit won't change the variable in cpp
	float AcceptanceRadius =8000; 	//How close can the AI tank gets to the player //AI will get 80 m near player

private:

	void BeginPlay() override;
	virtual void Tick(float deltatime) override;



};
	











/* 
ATank* GetAIControlledTank() const;



	ATank* GetPlayerTank() const;
*/
