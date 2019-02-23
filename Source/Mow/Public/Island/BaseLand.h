// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Building/BaseBuilding.h"

#include "BaseLand.generated.h" 

UCLASS()
class MOW_API ABaseLand : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseLand();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	bool MyBuild;
	 
	ABaseBuilding * Builder;

	/** 
	* Status of the island in front of the building construction
	* 0 -  // Nothing on the island, you can build on it
	* 1-    // Island zarezirvirovan under building
	* 2 -   // On the island there is a building
	* 3 -   // on the island built building opponent
	* 4 -   // on the island can not be built
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buildung")
		bool StatusBuildung;
};
