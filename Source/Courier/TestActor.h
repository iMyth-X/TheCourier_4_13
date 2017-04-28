// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"

//#include "Runtime/Online/Voice/Public/Voice.h"
//#include "C:/Program Files (x86)/Epic Games/4.13/Engine/Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Public/OnlineSubsystemUtils.h"

#include "Voice.h"
#include "OnlineSubsystemUtils.h"
#include "Sound/SoundWaveProcedural.h"




#include "TestActor.generated.h"


UCLASS()
class COURIER_API ATestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	const uint32 maxBytes = 2000;

	UPROPERTY()
	float VoiceCaptureVolume;

	UPROPERTY()
		bool VoiceCaptureTest;
	UPROPERTY()
		bool PlayVoiceCaptureFlag;

	UPROPERTY()
		FTimerHandle VoiceCaptureTickTimer;
	UPROPERTY()
		FTimerHandle PlayVoiceCaptureTimer;

	TSharedPtr<class IVoiceCapture> VoiceCapture;

	UPROPERTY()
		USoundWaveProcedural* VoiceCaptureSoundWaveProcedural;
	UPROPERTY()
		UAudioComponent* VoiceCaptureAudioComponent;
	
	UPROPERTY()
		TArray<uint8> VoiceCaptureBuffer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = default)
		bool ShouldAnimateMouth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = default)
	 float VolumeThreshold;

	UFUNCTION()
		void VoiceCaptureTick();

	UFUNCTION()
		void PlayVoiceCapture();

	
	
};
