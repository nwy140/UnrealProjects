// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankMovementComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"	
#include "Engine/World.h"
// Sets default values
ATank::ATank()
{
	// Set this pawn to		 call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); //Need for BP to run! //if you don't call super , Blueprints will  not call the entire BeginPlay method

}




void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds; //difference in time between currentime and lastfiretime more than reloadtime 
	
	if (!ensure(Barrel)) { return; }
	if ( isReloaded) {
	// spawn a projectile at the socket location at the barrel
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile"))); //You must include Projectile.h , as well as UTankBarrel.h
	Projectile->LaunchProjectile(LaunchSpeed);
	LastFireTime = FPlatformTime::Seconds();
	}
}