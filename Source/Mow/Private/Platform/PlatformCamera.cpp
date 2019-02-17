// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformCamera.h"

// Sets default values
APlatformCamera::APlatformCamera(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	UE_LOG(LogTemp, Warning, TEXT("APlatformCamera::BeginPlay 2"));
}

// Called when the game starts or when spawned
void APlatformCamera::BeginPlay()
{
	Super::BeginPlay(); 
		if (Fly)
		{
			UE_LOG(LogTemp, Warning, TEXT("APlatformCamera::BeginPla Fly"));
			Fly->SetRelativeLocation(FVector(0.0f, 0.0f, -20.f));
		}
		else {
		}
		 

}
