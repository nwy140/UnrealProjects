// Copyright SilentWolfStudios SDN BHD

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EmptyActor.generated.h"

UCLASS()
class BATTLETANK_API AEmptyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEmptyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	int Print(int NumberToPrint);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
