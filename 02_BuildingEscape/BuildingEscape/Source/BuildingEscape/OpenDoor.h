// Copyright Ng Wei Yuen

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

//you need to declare this macro to	create a BlueprintAssignable UPROPERTY
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);		//create FonOpenRequest class event

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnOpen;
	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnClose;

private:
	//UPROPERTY(EditAnywhere)
	//float OpenAngle = -90.0f; //shows a non editable OpenAngle Property in details in UEEditor
						 // this macro does a strange cut and paste in our code before it actually compiles // macros don't need semi colon
						 //macro parameter has no relevant auto complete because visual studio does not know what is going on for macros
						 //make sure there is no space after UProperty

	UPROPERTY(EditAnywhere)				// when intializing pointer ,always set it to nullptr to  let yourself know it is pointing to null at the start to avoid crash
		ATriggerVolume* PressurePlate = nullptr; // TriggerVolume pointer shows up at details via macro , and can be edited	
									//UPROPERTY macro shows PressurePlate in details tab, click it, then select TriggerVolume object to associate with pressureplate
								   // to see what type an object is, drag it to world outliner,  see its type, then include its header and use intelisense to type its type in c++

	UPROPERTY(EditAnywhere)
	float TriggerMass = 30.f;

	AActor* Owner = nullptr;

	//return mass in kg
	float GetTotalMasssOfActorOnPlate();

};
