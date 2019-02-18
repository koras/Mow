// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "AttributesComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MOW_API UAttributesComponent : public UActorComponent
{
	GENERATED_BODY()



public:	
	// Sets default values for this component's proper12ties
	UAttributesComponent();


	/*
	*  ѕроисходит ли героем абордаж острова
	*/
	UPROPERTY(EditAnywhere, Category = "Island boarding", BlueprintReadWrite)
		bool bIsAbordage = false;

	UPROPERTY(EditAnywhere, Category = "Heroes", BlueprintReadWrite)
		float CharacterCurrentManna;
	UPROPERTY(EditAnywhere, Category = "Heroes", BlueprintReadWrite)
		float CharacterMaxManna;
	UPROPERTY(EditAnywhere, Category = "Heroes", BlueprintReadWrite)
		float CharacterAddManna;


	UPROPERTY(EditAnywhere, Category = "Heroes", BlueprintReadWrite)
		float CharacterCurrentExperience;
	UPROPERTY(EditAnywhere, Category = "Heroes", BlueprintReadWrite)
		float CharacterMaxExperience;
	UPROPERTY(EditAnywhere, Category = "Heroes", BlueprintReadWrite)
		float CharacterAddExperience;
	bool HeroIsBuilding;
	UPROPERTY(EditAnywhere, Category = "Heroes", BlueprintReadWrite)
		float CharacterCurrentHealth;
	UPROPERTY(EditAnywhere, Category = "Heroes", BlueprintReadWrite)
		float CharacterMaxHealth;
	UPROPERTY(EditAnywhere, Category = "Heroes", BlueprintReadWrite)
		float CharacterAddHealth;
	// MOVE
	UPROPERTY(Replicated, EditAnywhere, Category = "Heroes")
		FVector BaseCharLocation;

	float AttackRadius;
	float AttackSpeed;
	bool CanAttack;
	bool IsMoveActor;

	// Characteristics of the hero
	float MoveMaxSpeed;
	float MoveCurrentSpeed;
	float MoveAcceleration;
	bool MoveCheckStop; // Check whether the hero is stopped
	FVector MoveCheckCoordinate; // The old coordinates for verification

	UFUNCTION(BlueprintCallable, Category = "Health")
		float GetHealth();
	UFUNCTION(BlueprintCallable, Category = "Health")
		float GetMaxHealth();
	UFUNCTION(BlueprintCallable, Category = "Health")
		void SetHealth(float Healt);

	UFUNCTION(BlueprintCallable, Category = "Manna")
		float GetManna();
	UFUNCTION(BlueprintCallable, Category = "Manna")
		float GetMaxManna();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
