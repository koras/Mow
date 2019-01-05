// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseMap.h"

// Sets default values
ABaseMap::ABaseMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseMap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

