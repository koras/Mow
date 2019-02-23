// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/AttributesComponent.h"
#include "BaseBuilding.generated.h"

UCLASS()
class MOW_API ABaseBuilding : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseBuilding();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle")
		UAttributesComponent *Attributes;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Bild Status")
		int32 Status;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Bild Status")
		float BuildProgress;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Bild Status")
		float BuildMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bild Status")
		bool MyBuild;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bild Status")
		bool BuildViewPort;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bild Status")
		bool MouseBuildViewPort;

	UPROPERTY(EditAnywhere, Category = "Property", BlueprintReadWrite)
		FString BuilderName;

	void StartSpawn();

	int32 stepBuild;
	const FVector CSphereLocation = FVector(0.0f, 0.0f, 150.0f);



	void DeadActor();

	UPROPERTY(EditAnywhere, Category = "Property", BlueprintReadWrite)
		int32 BuildFraction;
};
