// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Mow.h"
//#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "BoardingConstraintComponent.generated.h"

UCLASS()
class MOW_API UBoardingConstraintComponent : public UPhysicsConstraintComponent
{
	GENERATED_BODY()
public:

	bool bIsLandBoarding = false;

	UPROPERTY(EditAnywhere, Category = "Island boarding", BlueprintReadWrite)
		bool HUDabordage;

	UFUNCTION(BlueprintCallable, Category = "Island boarding")
		void RemovingIslandAbordage();

	UFUNCTION(BlueprintCallable, Category = "Island boarding")
		void startAbordage(AActor * whoPulls, AActor * whoArePulling);

	UFUNCTION(BlueprintCallable, Category = "Island boarding")
		void stopAbordage();



private:
	/*
	* Check if the island is busy and enable boarding animation
	* If the island is not busy, then we send the data that it is now
	* belongs to us and follows only us
	*/
	// UPROPERTY(EditAnywhere, Category = "Island boarding", BlueprintReadWrite)
	bool bIsAbordage();
 


};
