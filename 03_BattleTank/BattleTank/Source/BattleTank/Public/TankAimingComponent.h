// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"

#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

//Forward declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;

//Holds barrel's properties and Elevate method
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) // copied this line to TankBarrel 
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	void AimAt(FVector HitLocation, float LaunchSpeed);
	void AimAt(FVector HitLocation);


	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	EFiringState GetFiringState() const;
protected:
	UPROPERTY(BlueprintReadOnly , Category = "State" )
	EFiringState FiringState = EFiringState::Reloading;

private:
	UTankAimingComponent();
	
	bool IsBarrelMoving();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	//Tick Component method will be used if you are using an ActorComponent, Tick will be used if you are an Actor

	virtual void BeginPlay() override;

	void MoveBarrelTowards(FVector AimDirection);

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile>	 ProjectileBlueprint; // this allows you to select bo or cpp class AProjectile in Tank_BP
													  //UClass * ProjectileBlueprint; // Alternative use Tchar	, refer to unreal docs // this allows you to select projectile at Tank blueprints details at setup category  
													  //UClass * Allows you to choose absolutely anything
													  // for some reason it crashed so lets use TSubclass instead

	UPROPERTY(EditDefaultsOnly, Category = "Firing") //Edit defaults only means you can only edit the default value for all tanks , each tank will not have seperate values
	float ReloadTimeInSeconds = 3;

	double LastFireTime = 0;
	
	FVector AimDirection;
};
