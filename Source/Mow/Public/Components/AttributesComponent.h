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
//	UPROPERTY(EditAnywhere, Category = "Island boarding", BlueprintReadWrite)
//		bool bIsAbordage = false;

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
	bool HeroIsBuilding = false;
	UPROPERTY(EditAnywhere, Category = "Attributes", BlueprintReadWrite)
		float CharacterCurrentHealth;
	UPROPERTY(EditAnywhere, Category = "Attributes", BlueprintReadWrite)
		float CharacterMaxHealth;
	UPROPERTY(EditAnywhere, Category = "Attributes", BlueprintReadWrite)
		float CharacterAddHealth;
	// MOVE
	UPROPERTY(Replicated, EditAnywhere, Category = "Attributes")
		FVector BaseCharLocation;
	/*
	* Can the hero to move
	*/
	UPROPERTY(Replicated, EditAnywhere, Category = "Move")
		bool CharacterMove = true;
 

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

	float CharMapHeight = 50.f;
	bool GoIslandPoint = false;
	/*
	* Island boarder abordage
	*/ 
	bool IsMoveActor = false;


	void setbIsAbordage(bool Abordage);
	bool getbIsAbordage();
	void setbCanBuildIsland(bool Abordage);
	bool getbCanBuildIsland();
	void setbIsLandBoarding(bool Abordage);
	bool getbIsLandBoarding();
	void setSelectEraseToBoarding(bool EraseToBoarding);
	bool getSelectEraseToBoarding();
	 
	 
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
 
private:
	bool SelectEraseToBoarding = false;
	float fraction;
	float AttackRadius;
	float AttackSpeed;
	bool CanAttack; 

	// Characteristics of the hero
	float MoveMaxSpeed;
	float MoveCurrentSpeed;
	bool bIsLandBoarding = false;
	float MoveAcceleration;
	bool MoveCheckStop; // Check whether the hero is stopped
	FVector MoveCheckCoordinate; // The old coordinates for verification

	bool bIsAbordage = false;
	bool MyHero;
	bool bstop_anim_pawn = false;

	int32 AdversaryType = 2;
	//UPROPERTY(Replicated, EditAnywhere, Category = "Build")
		bool bCanBuildIsland = false;

	bool bReplicates = true;
	bool bstop_anim_move = false;
	bool bstart_anim_move = false;
	void AddTimeHealth(); 
};
