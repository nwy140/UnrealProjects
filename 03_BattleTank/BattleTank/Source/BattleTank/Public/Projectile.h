//// Fill out your copyright notice in the Description page of Project Settings.
//
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	void LaunchProjectile(float speed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor*  OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult&  Hit);

	// Needs to be protected so BP can modify the one inherited to BP from original cpp to avoid copying/	UProjectileMovementComponent* ProjectileMovement = nullptr;
	UProjectileMovementComponent* ProjectileMovement = nullptr;


	UPROPERTY(VisibleAnywhere , Category = "Components")
	UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* LaunchBlast= nullptr;

	UPROPERTY(VisibleANywhere, Category = "Components")
	UParticleSystemComponent* ImpactBlast = nullptr; 

};
