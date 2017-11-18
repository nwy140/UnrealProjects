// Copyright Ng Wei Yuen

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"

#include "Grabber.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

#pragma region DeclareVariables
	float Reach = 100.f;
#pragma endregion

#pragma region DeclarePointers
	//You got to include headers for every class component you are using
	UPhysicsHandleComponent * PhysicHandle = nullptr; //Pointer to other component , in same object
	UInputComponent * InputComponent = nullptr;
#pragma endregion

#pragma region DeclareMethods
	// Ray cast and grab what's in reach
	void Grab();
	
	//Called when grab is released
	void Release();

	//Find (assumed) attached physics handle
	void FindPhysicsHandleComponent();

	//Setup (assumed) input component
	void SetupInputComponent();

	//Return hit for first physic body in reach
	const FHitResult GetFirstPhysicBodyInReach();

#pragma endregion
};
