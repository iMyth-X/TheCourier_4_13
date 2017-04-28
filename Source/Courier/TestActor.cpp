// Fill out your copyright notice in the Description page of Project Settings.

#include "Courier.h"
#include "TestActor.h"


// Sets default values
ATestActor::ATestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Initialisation:
	VoiceCapture = FVoiceModule::Get().CreateVoiceCapture();
	VoiceCapture->Start();

	VoiceCaptureAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("VoiceCaptureAudioComponent"));
	VoiceCaptureAudioComponent->SetupAttachment(RootComponent);
	VoiceCaptureAudioComponent->bAutoActivate = true;
	VoiceCaptureAudioComponent->bAlwaysPlay = true;
	VoiceCaptureAudioComponent->PitchMultiplier = 0.85f;
	VoiceCaptureAudioComponent->VolumeMultiplier = 1.f;

	VoiceCaptureSoundWaveProcedural = NewObject<USoundWaveProcedural>();
	VoiceCaptureSoundWaveProcedural->SampleRate = 22050;
	VoiceCaptureSoundWaveProcedural->NumChannels = 1;
	VoiceCaptureSoundWaveProcedural->Duration = INDEFINITELY_LOOPING_DURATION;
	VoiceCaptureSoundWaveProcedural->SoundGroup = SOUNDGROUP_Voice;
	VoiceCaptureSoundWaveProcedural->bLooping = false;
	VoiceCaptureSoundWaveProcedural->bProcedural = true;
	VoiceCaptureSoundWaveProcedural->Pitch = 0.85f;
	VoiceCaptureSoundWaveProcedural->Volume = 1.f;


}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(PlayVoiceCaptureTimer, this, &ATestActor::PlayVoiceCapture, 0.4f, true, 0.f);
	
}

// Called every frame
void ATestActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	VoiceCaptureTick();

}

void ATestActor::VoiceCaptureTick() {

	if (!VoiceCapture.IsValid()) {
		return;
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("audioActive"));


	uint32 VoiceCaptureBytesAvailable = 0;
	EVoiceCaptureState::Type CaptureState = VoiceCapture->GetCaptureState(VoiceCaptureBytesAvailable);

	VoiceCaptureBuffer.Reset();
	PlayVoiceCaptureFlag = false;

	if (CaptureState == EVoiceCaptureState::Ok && VoiceCaptureBytesAvailable > 0) {

		int16_t VoiceCaptureSample;
		uint32 VoiceCaptureReadBytes;
		float VoiceCaptureTotalSquared = 0;

		VoiceCaptureBuffer.SetNumUninitialized(VoiceCaptureBytesAvailable);

		VoiceCapture->GetVoiceData(VoiceCaptureBuffer.GetData(), VoiceCaptureBytesAvailable, VoiceCaptureReadBytes);

		for (uint32 i = 0; i < (VoiceCaptureReadBytes / 2); i++)
			{
				VoiceCaptureSample = (VoiceCaptureBuffer[i * 2 + 1] << 8) | VoiceCaptureBuffer[i * 2];
				VoiceCaptureTotalSquared += ((float)VoiceCaptureSample * (float)VoiceCaptureSample);
			
			}
		float VoiceCaptureMeanSquare = (2 * (VoiceCaptureTotalSquared / VoiceCaptureBuffer.Num()));
		float VoiceCaptureRms = FMath::Sqrt(VoiceCaptureMeanSquare);
		float VoiceCaptureFinalVolume = ((VoiceCaptureRms / 32768.0) * 200.0f);

		VoiceCaptureVolume = VoiceCaptureFinalVolume;
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Volume: %f"), VoiceCaptureFinalVolume));
		
		if (VoiceCaptureFinalVolume >= VolumeThreshold)
		{
			ShouldAnimateMouth = true;
		}
		else
			ShouldAnimateMouth = false;

		//VoiceCaptureSoundWaveProcedural->QueueAudio(VoiceCaptureBuffer.GetData(), VoiceCaptureReadBytes);
		//VoiceCaptureAudioComponent->SetSound(VoiceCaptureSoundWaveProcedural);

		//PlayVoiceCaptureFlag = true;

	}


}

void ATestActor::PlayVoiceCapture() {

	if (!PlayVoiceCaptureFlag)
	{
		VoiceCaptureAudioComponent->FadeOut(0.3f, 0.f);
		return;
	}

	if (VoiceCaptureAudioComponent->IsPlaying())
		return;

	VoiceCaptureAudioComponent->Play();
}

