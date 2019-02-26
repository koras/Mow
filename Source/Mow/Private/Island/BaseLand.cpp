// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseLand.h"

// Sets default values
ABaseLand::ABaseLand()
{
	Attributes = CreateDefaultSubobject<UAttributesComponent>(TEXT("Attribute"));
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseLand::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseLand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseLand::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

