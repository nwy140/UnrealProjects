// Fill out your copyright notice in the Description page of Project Settings.

/*
* TankTrack is used to set maximum driving force, and to apply forces to the tank
*/
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}
void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit); //Register Track to generate hit events first //Register delegate at BeginPlay for OnHit() Events
}


void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction); //Code won't run properly unless you call Super method or you have blueprint that inherits from this
	//UE_LOG(LogTemp, Warning, TEXT("TRAKKAD"));  //If ticking doesn't work , go to BP Hierachy , Delete and add TankTrack again
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	// Workout the required acceleration this frame to correct
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime *GetRightVector();
	// Calculate and apply sideways for (F=MA)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2;
	TankRoot->AddForce(CorrectionAcceleration);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	UE_LOG(LogTemp, Warning, TEXT(" OnHit() called!!!"), *GetName());
}

void UTankTrack::SetThrottle(float Throttle)
{

	Throttle = FMath::Clamp<float>(Throttle, -0.5, 0.5	);

	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()); //GetOwner gets Tank_Bp, GetRootComponent Get Tank Mesh but it gets a scene component which you can't add force to it, so you have to cast it down to PrimitiveComponent
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}



