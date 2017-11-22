/// Copyright Ng Wei Yuen

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"



#include "DrawDebugHelpers.h"

#define OUT
/// Sets default values for this component's properties
UGrabber::UGrabber()
{
	/// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	/// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

/// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	///Find (assumed) attached physichandler component
	FindPhysicsHandleComponent();

	///Setup (assumed) attached Input Component
	SetupInputComponent();
}

#pragma region DefineMethods 

#pragma region DefineBindActionMethods
void UGrabber::Grab()
{
	//Avoid using semicolons at the end of macros to avoid bugs in the future //UE_LOG(LogTemp, Warning, TEXT("Grab pressed"))
	// LINE TRACE and see if we reach any actors with physicsbody collision channel set
	auto HitResult = GetFirstPhysicBodyInReach(); //auto is a c++ 11 type that automatically decides an appropriate type for you
	auto ComponentToGrab = HitResult.GetComponent(); // get mesh in our case
	auto ActorHit = HitResult.GetActor();

	// if we hit something then attach a physic handle
	if (ActorHit) { // if actor hit not equal null
		if (!PhysicHandle) { return; }
		//TODO attach physic handle	
		PhysicHandle->GrabComponentAtLocationWithRotation( //Grab Component method no longer work with new API, so use GrabcomponentwithLocation
			ComponentToGrab,
			NAME_None, // no bones needed
			ComponentToGrab->GetOwner()->GetActorLocation(),  // must #include "Components/PrimitiveComponent.h" or else you can't refer to other object components other then the object with current class attached
			FRotator(0) //allow rotation  // true doesnot work with new API, use FROTATOR(0) instead
		);
	}
}

void UGrabber::Release()
{
	if (!PhysicHandle) { return; }
	PhysicHandle->ReleaseComponent();
}
#pragma endregion 

#pragma region DefineComponentMethods
///Look for attached physics Component
void UGrabber::FindPhysicsHandleComponent()
{
	PhysicHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();//<> is generic signature //specify class here without relying on intelisense
	if (PhysicHandle == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("PhysicHandler component not found in object %s"), *(GetOwner()->GetName()));
	}
}

/// Setup attached Input Component
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (!InputComponent) {
		UE_LOG(LogTemp, Error, TEXT("InputComponent not found"))
			return;
	}
	if (InputComponent) {///	Input Component found
		//Bind the input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Input component not found"), *(GetOwner()->GetName()));
	}
}
#pragma endregion 
#pragma endregion

/// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// if physics handle is attached
	if (!PhysicHandle) { return; }
	if (PhysicHandle->GrabbedComponent) {

		// move the object we are handling	
		PhysicHandle->SetTargetLocation(GetReachLineEnd());
	}


}

const FHitResult UGrabber::GetFirstPhysicBodyInReach()
{
	/// Line-trace (AKA Ray-cast) out to reach distance  /// imagine superman laser eyes logging
	FHitResult HitResult;
	///Setup query parameter
	FCollisionQueryParams	TraceParameters(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType( //Detect Object hit 
		OUT HitResult, /// mark it as OUT parameter
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters

	); ////LineTraceMulti will pass through multiple objects and report multiple answers	

	return HitResult;
}

FVector UGrabber::GetReachLineEnd()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT	PlayerViewPointLocation, ///Set ViewPointLocation
		OUT	PlayerViewPointRotation ///OUT actually does nothing //// Just marking parameters with OUT to show the variables you need to log out
	); ///Go from world, then get player, then get view of player

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}

FVector UGrabber::GetReachLineStart()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT	PlayerViewPointLocation, ///Set ViewPointLocation
		OUT	PlayerViewPointRotation ///OUT actually does nothing //// Just marking parameters with OUT to show the variables you need to log out
	); ///Go from world, then get player, then get view of player

	return PlayerViewPointLocation;
}