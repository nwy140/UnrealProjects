// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h"





void ATankPlayerController::BeginPlay()

{

	Super::BeginPlay(); // makes sure BeginPlay on super class is called
	if (!GetPawn()) { return; } // e.g if not possesing // We don't use ensure here because at runtime we may not possess the tank
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);

}

void ATankPlayerController::Tick(float deltatime)

{

	Super::Tick(deltatime);

	AimTowardsCrosshair();

}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn) {

		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		PossessedTank->OnDeath.AddDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}
}

void ATankPlayerController::OnPossessedTankDeath()
{
	StartSpectatingOnly();
}

void ATankPlayerController::AimTowardsCrosshair()

{
	if (!GetPawn()) { return; } // e.g if not possesing // We don't use ensure here because at runtime we may not possess the tank
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation; //OUT parameter
	bool bGotHitLocation =GetSightRayHitLocation(HitLocation);
	//UE_LOG(LogTemp, Warning, TEXT("bGotHitLocation: %i"),bGotHitLocation);
	if (bGotHitLocation) { //Has "side-effect" , is going t0o line trace
		AimingComponent->AimAt(HitLocation);//Refering to Tank Pawn, regardless possed by player or AI , so pass name from subclass instead, 
		//if hits the lanscape

		// TODO: Tell controlledtank to aim at this point
	}
}

// GetWorldLocation of linetrace through crosshair	 , true if hit linescape		
bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation) const
{
#pragma region Find crosshair position
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation = FVector2D(ViewportSizeX*CrossHairXLocation, ViewportSizeY* CrossHairYLocation); /// auto is a new C++11 type that automatically sets the correct class type for you
	//UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString())
#pragma endregion

#pragma region "De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		// Line-trace alog that look direction, and see what we hit (up to max range)
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);
		//UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *LookDirection.ToString()) // due to pythagoras theorem , the value, hypotamus is always one, therefore log Vectors does not appear more than 1 for Deprojecttoscreen	
		
	}
#pragma endregion
	return false;
}
bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LookDirection * LineTraceRange;


	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Camera)// Visible means hit anything that you can see
		) {

		//Set hit Location	
		OutHitLocation = HitResult.Location;

		return true;
	}
	else {
		OutHitLocation = FVector(0, 0, 0); // just to make sure, although it is usually already 0 if linetrace hits nothing
		return false; //Line trace failed
	}
}


bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection)  const// bool because we want to know whether it works
{
	// "De-project" the screen position of the crosshair to a world direction
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);

}









