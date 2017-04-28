// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CommandLineActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COURIER_API UCommandLineActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCommandLineActorComponent();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Command Line Arguments")
	uint8 GetNetworkComponentEnumValue();
};
