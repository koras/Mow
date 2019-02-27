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

	UPROPERTY(EditAnywhere, Category = "Attributes", BlueprintReadWrite)
		float CharacterCurrentManna;
	UPROPERTY(EditAnywhere, Category = "Attributes", BlueprintReadWrite)
		float CharacterMaxManna;
	UPROPERTY(EditAnywhere, Category = "Attributes", BlueprintReadWrite)
		float CharacterAddManna;


	UPROPERTY(EditAnywhere, Category = "Attributes", BlueprintReadWrite)
		float CharacterCurrentExperience;
	UPROPERTY(EditAnywhere, Category = "Attributes", BlueprintReadWrite)
		float CharacterMaxExperience;
	UPROPERTY(EditAnywhere, Category = "Attributes", BlueprintReadWrite)
		float CharacterAddExperience;
	bool HeroIsBuilding;
	UPROPERTY(EditAnywhere, Category = "Attributes", BlueprintReadWrite)
		float CharacterCurrentHealth;
	UPROPERTY(EditAnywhere, Category = "Attributes", BlueprintReadWrite)
		float CharacterMaxHealth;
	UPROPERTY(EditAnywhere, Category = "Attributes", BlueprintReadWrite)
		float CharacterAddHealth;
	// MOVE
	UPROPERTY(Replicated, EditAnywhere, Category = "Attributes")
		FVector BaseCharLocation;

 

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		float GetHealth();
	UFUNCTION(BlueprintCallable, Category = "Attributes")
		float GetMaxHealth();
	UFUNCTION(BlueprintCallable, Category = "Attributes")
		void SetHealth(float Healt);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		float GetManna();
	UFUNCTION(BlueprintCallable, Category = "Attributes")
		float GetMaxManna();
	

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetFraction();

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		void SetFraction(float tmpfraction);


	UFUNCTION(BlueprintCallable, Category = "Attributes")
		float GetCurrentProcent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//UPROPERTY(EditAnywhere, Category = "Hero property", BlueprintReadWrite)
	//	bool MyHero;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		bool GetMyHero();

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		bool SetMyHero(bool tmp);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;
 
private:
	float fraction;
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

	bool MyHero;

	void AddTimeHealth();
};
