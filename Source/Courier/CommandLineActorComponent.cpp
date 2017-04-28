// Fill out your copyright notice in the Description page of Project Settings.

#include "Courier.h"
#include "CommandLineActorComponent.h"


// Sets default values for this component's properties
UCommandLineActorComponent::UCommandLineActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

uint8 UCommandLineActorComponent::GetNetworkComponentEnumValue()
{
	FString fileName;
	uint8 actorType;

	if (!(FParse::Value(FCommandLine::Get(), TEXT("NetworkComponent"), actorType)))
		actorType = 0;

	return actorType;
}
