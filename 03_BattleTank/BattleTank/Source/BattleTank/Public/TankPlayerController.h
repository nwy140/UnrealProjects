// Fill out your copyright notice in the Description page of Project Settings.



#pragma once



#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"




#include "TankPlayerController.generated.h"



/**

*

*/

class ATank;
class UTankAimingComponent;

UCLASS()

class BATTLETANK_API ATankPlayerController : public APlayerController

{

	GENERATED_BODY()

public:


protected: 
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const; //protected so Blueprints can edit and access PlayerTank

	UFUNCTION(BlueprintImplementableEvent)
	void FoundAimingComponent(UTankAimingComponent* AimCompRef); //Since this is blueprint implementable, you don't need to implement/define this in cpp file, you can just implement it on blueprints
private:
#pragma region DeclareVariables 
	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5;   /// crosshair 50% across screen
	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.33333; /// cross hair 1/9 across screen
	UPROPERTY(EditDefaultsOnly)	
	float LineTraceRange = 100000; // cm to meters
#pragma endregion

#pragma region DeclarePointers
	///You got to include headers for every class component you are using
	///Eg :	UInputComponent * InputComponent = nullptr;
#pragma endregion

#pragma region DeclareMethods
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const;
	bool GetLookVectorHitLocation( FVector LookDirection , FVector& HitLocation) const;
	//start the tank moving the barrel so that a shot would hit where the crosshair  intersects the world
#pragma region EngineMethodsoverride
	void BeginPlay() override;

	virtual void Tick(float deltatime) override;
#pragma endregion
#pragma endregion


	

};