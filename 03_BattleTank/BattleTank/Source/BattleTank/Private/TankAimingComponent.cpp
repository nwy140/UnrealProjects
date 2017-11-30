// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent * BarrelToSet)
{
	Barrel = BarrelToSet;

}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; } // protecting reference
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile")); // Gets location of socket projectile, if projectile not found returns location of barrel


	if (UGameplayStatics::SuggestProjectileVelocity( //Calculate OutLaunchVelocity // UGameplayStatic::   , method called using :: because it is a static method
		this,
		OutLaunchVelocity,
		StartLocation, 
		HitLocation, 
		LaunchSpeed , 
		false,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace)
		)
	{

		auto AimDirection = OutLaunchVelocity.GetSafeNormal(); // unit vector
		UE_LOG(LogTemp, Warning, TEXT("Aiming at %s"),*AimDirection.ToString())
	}//auto  OurTankname = GetOwner()->GetName();
	//auto BarrelLocation = Barrel->GetComponentLocation().ToString();
	//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *OurTankname, *HitLocation.ToString(), *BarrelLocation);

}
