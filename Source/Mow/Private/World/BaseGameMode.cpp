// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseGameMode.h"

ABaseGameMode::ABaseGameMode()
{
	PrimaryActorTick.bCanEverTick = false;
	PlayerControllerClass = AWindController::StaticClass();
	DefaultPawnClass = AManagerCamera::StaticClass();
}

void ABaseGameMode::BeginPlay()
{
	Super::BeginPlay();
}



void ABaseGameMode::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
}
