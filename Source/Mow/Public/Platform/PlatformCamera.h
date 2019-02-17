// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlatform.h"
#include "GameFramework/Actor.h"

#include "ConstructorHelpers.h"

#include "PlatformCamera.generated.h"

UCLASS()
class MOW_API APlatformCamera : public ABasePlatform
{
	GENERATED_UCLASS_BODY()
	
//public:	
	// Sets default values for this actor's properties
	//APlatformCamera();

 
	// Called every frame
//	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	 

};
