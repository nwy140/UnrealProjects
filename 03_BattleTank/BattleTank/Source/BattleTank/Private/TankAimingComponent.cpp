// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; } // protecting reference
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile")); // Gets location of socket projectile, if projectile not found returns location of barrel

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity( //Calculate OutLaunchVelocity // UGameplayStatic::   , method called using :: because it is a static method
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal(); // unit vector
		MoveBarrelTowards(AimDirection); //pass AimDirection

		//UE_LOG(LogTemp, Warning, TEXT("Aiming at %s"), *AimDirection.ToString())
	}//auto  OurTankname = GetOwner()->GetName();
	//auto BarrelLocation = Barrel->GetComponentLocation().ToString();
	//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *OurTankname, *HitLocation.ToString(), *BarrelLocation);

}
void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// Work out difference between current barrel rotation , and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation(); //GetForwardVector Gets direction
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	//UE_LOG(LogTemp, Warning, TEXT("DeltaRotator: %s"), *DeltaRotator.ToString())

		Barrel->Elevate(5); //TODO: remove magic number

	}
