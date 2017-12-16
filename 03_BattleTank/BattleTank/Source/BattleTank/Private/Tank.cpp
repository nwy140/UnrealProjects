// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"	
#include "Engine/World.h"
// Sets default values
ATank::ATank()
{
	// Set this pawn to		 call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s Donkey: Tank C++ Construct"), *GetName() ); // constructor only calls for first tank spawns , if it is already spawned, it wont be called
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); //Need for BP to run! //if you don't call super , Blueprints will  not call the entire BeginPlay method
	auto TankName = GetName(); //only when you call beginplay , constructor will be called before beginplay, otherwise it will only call once
	UE_LOG(LogTemp, Warning, TEXT("%s Donkey: Tank C++ BeginPlay"), *GetName()); // constructor only calls for first tank spawns

}

void ATank::AimAt(FVector HitLocation)
{
	if (!TankAimingComponent) { return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}



void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds; //difference in time between currentime and lastfiretime more than reloadtime 
	
	if (Barrel && isReloaded) {
	// spawn a projectile at the socket location at the barrel
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile"))); //You must include Projectile.h , as well as UTankBarrel.h
	Projectile->LaunchProjectile(LaunchSpeed);
	LastFireTime = FPlatformTime::Seconds();
	}
}