// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" 
#include "Heroes/BaseCharacter.h"
#include "ConstructorHelpers.h"
#include "Warrior.generated.h"

/**
 * 
 */
UCLASS()
class MOW_API AWarrior : public ABaseCharacter
{
	GENERATED_UCLASS_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaTimeX);

	//	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	UFUNCTION(Category = Default)
		void OverlapBeginComponent(UPrimitiveComponent* pComponent);
	UFUNCTION(Category = Default)
		virtual void AnimationGo();
	UFUNCTION(Category = Default)
		virtual void AnimationSTOP();
	UFUNCTION(Category = Default)
		virtual void AnimationStart();

	void GoBuild();
};
