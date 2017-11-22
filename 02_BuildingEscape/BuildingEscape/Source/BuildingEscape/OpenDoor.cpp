// Copyright Ng Wei Yuen

#include "OpenDoor.h"
#include <GameFramework/Actor.h>
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	if (PressurePlate == nullptr) {
		UE_LOG(LogTemp,Error,TEXT("%s missing PressurePlate"), * Owner->GetName())
	}

}

void UOpenDoor::OpenDoor() // Quick actions - Extract function
{
	//Find Owning Actor

	//Create a Rotator
	//FRotator NewRotation = FRotator(0.f, -60.f, 0.f);// FRotater Constructor Pass X,Y,Z as pitch , yaw and roll
													 // pitch is x axis up and down, Yaw is ground left and right, Roll is z axis up and down
													 //Set the door Rotation
	// Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
	OnOpenRequest.Broadcast(); //set C++ events to be used in blueprints//Do rotation in blueprint in this case

	//UE_LOG(LogTemp, Error, TEXT("%s"), Rotater.ToString());
}


void UOpenDoor::CloseDoor() // Quick actions - Extract function
{
	//Find Owning Actor

	////Create a Rotator
	//FRotator NewRotation = ();// FRotater Constructor Pass X,Y,Z as pitch , yaw and roll
													 // pitch is x axis up and down, Yaw is ground left and right, Roll is z axis up and down
													 //Set the door Rotation
	Owner->SetActorRotation(FRotator(0.f, 0.f, 0.f));


	//UE_LOG(LogTemp, Error, TEXT("%s"), Rotater.ToString());
}



// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Poll the triggervolume every frame


	//If the ActorThatOpens is in the volume
	if (GetTotalMasssOfActorOnPlate() >= 30.f)	//if you hard code something ,you an make it into a parameter
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds(); //GetTimeSeconds is the number of secnds passed since gamestarted

	}
	if ((GetWorld()->GetTimeSeconds() - (LastDoorOpenTime)) > DoorCloseDelay)
	{
		CloseDoor();
	}
	//Check if time to close the door


}

float UOpenDoor::GetTotalMasssOfActorOnPlate()
{
	float TotalMass = 0.f;
	if (!PressurePlate) {	return TotalMass; }
	//find all overlapping actors
	TArray<AActor*> OverlappingActors; //TArray is a type mean for elements of the same type, similar to the regular array, //int array[] is the same as TArray<int>
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	//iterate through them adding their masses

	for (const auto* Actor : OverlappingActors) { // const to show that actor does not change here, we just receive the actor
													// auto is auto class type				
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();// Get Owner is getting owner of component, not Actor Object, if you do it to object, it will be a nullpointer thus crashing the engine
		UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"),* (Actor->FindComponentByClass<UPrimitiveComponent>()->GetOwner()->GetName()))
			// Table and chair doesn't generate events, so you have to go to physics and check generateevents on collision
	}

	return TotalMass;
}