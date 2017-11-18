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

	///UE_LOG(LogTemp, Warning, TEXT("Grabber %s reporting for duty!"), *(GetOwner()->GetName()));

	///Find (assumed) attached physichandler component
	FindPhysicsHandleComponent();

	///Setup (assumed) attached Input Component
	SetupInputComponent();

}

#pragma region DefineMethods 

#pragma region DefineBindActionMethods
void UGrabber::Grab() {
	//Avoid using semicolons at the end of macros to avoid bugs in the future
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"))
		// LINE TRACE and see if we reach any actors with physicsbody collision channel set
	auto HitResult = GetFirstPhysicBodyInReach(); //auto is a c++ 11 type that automatically decides an appropriate type for you
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	// if we hit something then attach a physic handle
	if (ActorHit) { // if actor hit not equal null
		//TODO attach physic handle	
		PhysicHandle->GrabComponentAtLocationWithRotation( //Grab Component method no longer work with new API, so use GrabcomponentwithLocation
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),  // must #include "Components/PrimitiveComponent.h" or else you can't refer to other object components other then the object with current class attached
			FRotator(0) //allow rotation  // true doesnot work with new API, use FROTATOR(0) instead
		);
	}
}	

void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Grab released"))
		//TODO release physic handle
		PhysicHandle->ReleaseComponent();
}
#pragma endregion 

#pragma region DefineComponentMethods
///Look for attached physics Component
void UGrabber::FindPhysicsHandleComponent() {
	PhysicHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();//<> is generic signature //specify class here without relying on intelisense
	if (PhysicHandle) {
		//PhysicHandler is found
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("PhysicHandler component not found in object %s"), *(GetOwner()->GetName()));
	}

}

/// Setup attached Input Component
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {///	Input Component found
		UE_LOG(LogTemp, Warning, TEXT("Input component found in object %s"), *(GetOwner()->GetName()));
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
#pragma region tmp
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT	PlayerViewPointLocation, ///Set ViewPointLocation
		OUT	PlayerViewPointRotation ///OUT actually does nothing //// Just marking parameters with OUT to show the variables you need to log out
	); ///Go from world, then get player, then get view of player


	   ///TODO: LOG out to test
	   ///UE_LOG(LogTemp, Warning, TEXT("Location : %s , Rotation : %s "), *(PlayerViewPointLocation.ToString()), *(PlayerViewPointRotation.ToString()));

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
#pragma endregion 
	// if physics handle is attached
	if (PhysicHandle->GrabbedComponent){
		
		// move the object we are handling	
		PhysicHandle->SetTargetLocation(LineTraceEnd);
	}
	

}



const FHitResult UGrabber::GetFirstPhysicBodyInReach()
{	///Get player view point this tick

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT	PlayerViewPointLocation, ///Set ViewPointLocation
		OUT	PlayerViewPointRotation ///OUT actually does nothing //// Just marking parameters with OUT to show the variables you need to log out
	); ///Go from world, then get player, then get view of player


	   ///TODO: LOG out to test
	   ///UE_LOG(LogTemp, Warning, TEXT("Location : %s , Rotation : %s "), *(PlayerViewPointLocation.ToString()), *(PlayerViewPointRotation.ToString()));

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
	/// Draw a red trace in the world to visualize
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(255, 0, 0),
		false, /// won't disapper
		0.f,
		0.f,
		10.f
	);

	///Setup query parameter
	FCollisionQueryParams	TraceParameters(FName(TEXT("")), false, GetOwner());

	/// Line-trace (AKA Ray-cast) out to reach distance  /// imagine superman laser eyes logging
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType( //Detect Object hit 
		OUT Hit, /// mark it as OUT parameter
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters

	); ////LineTraceMulti will pass through multiple objects and report multiple answers	

	   ///See what we hit
	AActor * ActorHit = Hit.GetActor();
	if (ActorHit) // Since this loads every frame, it will crash before hit is instantiated because it points to nullpointer, so you need to prevent this error with an if statement
	{
		UE_LOG(LogTemp, Warning, TEXT("Line Trace hit: %s"), *(ActorHit->GetName()));
	}
	return Hit;
}

