// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel; //Foward Declaration , causes blueprint to crash , therefore compilation errors
class AProjectile;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()
protected:
	
	
public:
	// Sets default values for this pawn's properties
	ATank();



	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();
private:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;




	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint; // this allows you to select bo or cpp class AProjectile in Tank_BP
	//UClass * ProjectileBlueprint; // Alternative use Tchar	, refer to unreal docs // this allows you to select projectile at Tank blueprints details at setup category  
									//UClass * Allows you to choose absolutely anything
										// for some reason it crashed so lets use TSubclass instead

	

	UPROPERTY(EditDefaultsOnly, Category="Firing" ) //Edit defaults only means you can only edit the default value for all tanks , each tank will not have seperate values
	float ReloadTimeInSeconds = 3;


	UTankBarrel* Barrel = nullptr; //TODO : Remove


	double LastFireTime = 0;


	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4000.f;

};
