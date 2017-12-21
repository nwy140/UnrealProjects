// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	UE_LOG(LogTemp,Warning,TEXT("Ticking"))
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
	if ((FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds) //difference in time between currentime and lastfiretime more than reloadtime 
	{
		FiringState = EFiringState::Reloading;
	}
	//TODO: Handle Lock State
}


void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; } // protecting reference
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile")); // Gets location of socket projectile, if projectile not found returns location of barrel

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity( //Calculate OutLaunchVelocity // UGameplayStatic::   , method called using :: because it is a static method
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace //Commenting this out cause bugs// Passing parameters even though default will be set if you don't pass may solve bugs with whether each frame found solution or not
	);
	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal(); // unit vector
		MoveBarrelTowards(AimDirection); //pass AimDirection
		float Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f : Aim solution found"), Time)

		//UE_LOG(LogTemp, Warning, TEXT("Aiming at %s"), *AimDirection.ToString())
	}//auto  OurTankname = GetOwner()->GetName();
	//auto BarrelLocation = Barrel->GetComponentLocation().ToString();
	//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *OurTankname, *HitLocation.ToString(), *BarrelLocation);
	
}
void UTankAimingComponent::Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}
void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret) ) { return; }

	// Work out difference between current barrel rotation , and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation(); //GetForwardVector Gets direction
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	//UE_LOG(LogTemp, Warning, TEXT("DeltaRotator: %s"), *DeltaRotator.ToString())

	Barrel->Elevate(DeltaRotator.Pitch); //TODO: remove magic number
	Turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::Fire()
{
	
	if (FiringState!=EFiringState::Reloading) {
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		// spawn a projectile at the socket location at the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile"))); //You must include Projectile.h , as well as UTankBarrel.h
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}
