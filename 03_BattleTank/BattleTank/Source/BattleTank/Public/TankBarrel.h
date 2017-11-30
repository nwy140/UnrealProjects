// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:  //Members can be accessed outside class

protected: //Members can be accessed only inside class and subclasses that inherits from that class

private: //Members can be accessed only inside class
#pragma region DeclareVariables
		 ///Eg:	float Reach = 100.f;
#pragma endregion

#pragma region DeclarePointers
		 ///You got to include headers for every class component you are using
		 ///Eg :	UInputComponent * InputComponent = nullptr;
#pragma region ExternalClass
		 ///Eg. UTankAimingComponent* TankAimingComponent = nullptr; ///Remember to initialize to nullptr
#pragma endregion

#pragma endregion

#pragma region DeclareMethods
		 ///Place any methods you are going to create here
		 ///Eg: void SetupInputComponent();
	void Elevate(float DegreesPerSecond);

#pragma region EngineMethodsoverride
	//void BeginPlay() override;

	//virtual void Tick(float deltatime) override;
#pragma endregion
#pragma endregion



	
};
