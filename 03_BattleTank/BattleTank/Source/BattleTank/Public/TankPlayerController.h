// Fill out your copyright notice in the Description page of Project Settings.



#pragma once



#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"



#include "Tank.h"

#include "TankPlayerController.generated.h"



/**

*

*/

UCLASS()

class BATTLETANK_API ATankPlayerController : public APlayerController

{

	GENERATED_BODY()

public:




private:
#pragma region DeclareVariables 
	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5;   /// crosshair 50% across screen
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333; /// cross hair 1/9 across screen
#pragma endregion

#pragma region DeclarePointers
	///You got to include headers for every class component you are using
	///Eg :	UInputComponent * InputComponent = nullptr;
#pragma endregion

#pragma region DeclareMethods
	ATank* GetControlledTank() const;
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const;
	//start the tank moving the barrel so that a shot would hit where the crosshair  intersects the world
#pragma region EngineMethodsoverride
	void BeginPlay() override;

	virtual void Tick(float deltatime) override;
#pragma endregion
#pragma endregion


	

};