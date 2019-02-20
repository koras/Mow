// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" 
#include "WindController.h"
#include "ManagerCamera.h"
#include "GameFramework/GameMode.h"
#include "BaseGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MOW_API ABaseGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ABaseGameMode();
		virtual void Tick(float DeltaSeconds) override;

		// Called when the game starts or when spawned
		virtual void BeginPlay() override;
};
