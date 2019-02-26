// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/AttributesComponent.h"

// Sets default values for this component's properties
UAttributesComponent::UAttributesComponent()
{
	CharacterAddHealth = 4.f;

	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAttributesComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UAttributesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	AddTimeHealth();
	// ...
}



float UAttributesComponent::GetHealth() {
	return CharacterCurrentHealth;
} 

float UAttributesComponent::GetMaxHealth() {
	return CharacterMaxHealth;
}


float UAttributesComponent::GetManna() {
	return CharacterCurrentManna;
}
float UAttributesComponent::GetMaxManna() {
	return CharacterMaxManna;
}
 

float UAttributesComponent::GetCurrentProcent() {
	return CharacterCurrentHealth / (CharacterMaxHealth / 100);
}
float UAttributesComponent::GetFraction() {
	return fraction;
}

void UAttributesComponent::SetFraction(float tmpfraction) {
	  fraction = tmpfraction;
} 

void UAttributesComponent::AddTimeHealth()
{
	SetHealth(CharacterAddHealth);
}

void UAttributesComponent::SetHealth(float Healt) {
	CharacterCurrentHealth += Healt;
	if (CharacterCurrentHealth >= CharacterMaxHealth)CharacterCurrentHealth = CharacterMaxHealth;

	//	UE_LOG(LogTemp, Warning, TEXT("CharacterCurrentHealth %f"), CharacterCurrentHealth);
}



void UAttributesComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//UE_LOG(LogTemp, Warning, TEXT("Replicated"));
// Replicate to everyone
//	DOREPLIFETIME(ABaseCharacter, CharacterMove);
//	DOREPLIFETIME(ABaseCharacter, BaseCharLocation);
}
