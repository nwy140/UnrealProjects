// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"


#pragma region DefineMethods
///Place methods for initilization from class
void UTankBarrel::Elevate(float DegreesPerSecond)
{
	// Move the barrel

	// Given a max elevation speed and the frame time
	UE_LOG(LogTemp, Warning, TEXT("Barrel->Elevate called at speed %f") , DegreesPerSecond)
}


#pragma region DefindBindActionMethods
///Place methods regarding binding actions here
#pragma endregion 

#pragma region DefineComponentMethods
///Place methods regarding accessing Components here
#pragma endregion

#pragma endregion

