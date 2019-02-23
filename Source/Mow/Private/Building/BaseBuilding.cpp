// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseBuilding.h"

// Sets default values
ABaseBuilding::ABaseBuilding()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseBuilding::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseBuilding::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

/**
*We subtract the cost of construction
*/
void ABaseBuilding::StartSpawn()
{
//	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGameWorldSettings::StaticClass(), TestCubeActorArray);
	//AGameWorldSettings* WorldSettings = Cast<AGameWorldSettings>(TestCubeActorArray[0]);
	//	UE_LOG(LogTemp, Warning, TEXT("We have written off the money 1"));
//	if (TestCubeActorArray[0]) {
//		WorldSettings->SubtractionGold(CostHome_1lvl);
//	}
}

void ABaseBuilding::DeadActor()
{
}