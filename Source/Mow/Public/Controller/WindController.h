// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "BaseCharacter.h" 
#include "WindController.generated.h"


USTRUCT()
struct FCharacterMove
{
	GENERATED_USTRUCT_BODY()
		ABaseCharacter* ActorCharacter;
	//	float Distance;
	FVector location;
	bool BusyPoint;
	TArray<int*> PointTriangle;
};

USTRUCT()
struct FSinCos
{
	GENERATED_USTRUCT_BODY()
		TArray<FVector2D> location;
	//default properties
	FSinCos()
	{
		location.Add(FVector2D(0.f, 1.f));		// 0 
		location.Add(FVector2D(0.86f, 0.5f));	// 60 
		location.Add(FVector2D(0.86f, -0.5f));	//120
		location.Add(FVector2D(0.f, -1.f));		//180
		location.Add(FVector2D(-0.866f, -0.5f)); //240
		location.Add(FVector2D(-0.866f, 0.5f)); //240
	}
};

USTRUCT()
struct FBusyPoint
{
	GENERATED_USTRUCT_BODY()
		FVector2D Coord;
	int NumPoint;
	int Drade;
	bool Ibusy;
};

USTRUCT()
struct FNeighborsPoint
{
	GENERATED_USTRUCT_BODY()
		int32 Center; // Центральная точка
	TArray<int32> Neighbors;
	TArray<FVector2D> Coord;
	FVector2D CoordCenter;
};



/**
 * 
 */
UCLASS()
class MOW_API AWindController : public APlayerController
{
	GENERATED_BODY()
	
};
