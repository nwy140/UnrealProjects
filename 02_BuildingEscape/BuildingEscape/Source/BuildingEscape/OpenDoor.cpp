// Copyright Ng Wei Yuen

#include "OpenDoor.h"
#include <GameFramework/Actor.h>
#include "Engine/World.h"


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
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();//player controller is the link between the pawn and the person using the machine
	// ... 

}

void UOpenDoor::OpenDoor() // Quick actions - Extract function
{
	//Find Owning Actor

	//Create a Rotator
	//FRotator NewRotation = FRotator(0.f, -60.f, 0.f);// FRotater Constructor Pass X,Y,Z as pitch , yaw and roll
													 // pitch is x axis up and down, Yaw is ground left and right, Roll is z axis up and down
													 //Set the door Rotation
	Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));


	//UE_LOG(LogTemp, Error, TEXT("%s"), Rotater.ToString());
}


void UOpenDoor::CloseDoor() // Quick actions - Extract function
{
	//Find Owning Actor

	////Create a Rotator
	//FRotator NewRotation = ();// FRotater Constructor Pass X,Y,Z as pitch , yaw and roll
													 // pitch is x axis up and down, Yaw is ground left and right, Roll is z axis up and down
													 //Set the door Rotation
	Owner->SetActorRotation(FRotator(0.f, 0.f, 0.f)	);


	//UE_LOG(LogTemp, Error, TEXT("%s"), Rotater.ToString());
}



// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Poll the triggervolume every frame

	//If the ActorThatOpens is in the volume
	if (PressurePlate->IsOverlappingActor(ActorThatOpens)) // write pressureplate && pressureplate = null to check if getting crashes
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds(); //GetTimeSeconds is the number of secnds passed since gamestarted
		
	}
	 if (		( 	GetWorld()->GetTimeSeconds()  - (LastDoorOpenTime )	) > DoorCloseDelay	) 
	{
		CloseDoor(); 
	}
	//Check if time to close the door


}

