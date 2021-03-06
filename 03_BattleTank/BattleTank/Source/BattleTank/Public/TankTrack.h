// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 *
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	// Set throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = "Input")
		void SetThrottle(float Throttle);

	//Max force per track in Newton
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 400000; //assume 40 tonne tank, and 1 g acceleration
private:
	UTankTrack();
	void BeginPlay();
	//virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) ;

	void ApplySidewaysForce();

	void DriveTrack();

	float CurrentThrottle = 0;
	
	UFUNCTION()
	void OnHit( UPrimitiveComponent* HitComponent, AActor*  OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult&  Hit);
};
