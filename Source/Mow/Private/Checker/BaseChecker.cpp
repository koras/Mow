// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseChecker.h"

// Sets default values
ABaseChecker::ABaseChecker()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseChecker::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseChecker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseChecker::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

