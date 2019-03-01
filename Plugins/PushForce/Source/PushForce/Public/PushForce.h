// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h" 
#include "DrawDebugHelpers.h"
//#include "Engine/World.h"

#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"

#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Modules/ModuleManager.h"

class FPushForceModule : public IModuleInterface//, public AAIController
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual int32 IsThisNumber42();


	virtual void SendPatrolTo(
		UPrimitiveComponent * Primitive, 
		AActor* BaseCharacter, 
		FVector Finish);

	virtual void SendMoveActor(
		UPrimitiveComponent * Primitive, 
		AActor* CharacterSingleFVector, 
		FVector FinishLocation);


	virtual bool TracePoint(AActor* ActorIgnor, FVector Start, FVector Finish);


	bool debag = false;
	// Called every frame
	//virtual void Tick(float DeltaSeconds) override;

	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

	// Current which will manage
	AActor* ToActorCharacter;
	AActor* Character;

	//	ABaseCharacter*  Character;

	UPrimitiveComponent * PrimitivePawn;

//	Logic* ALogic;
	float indexZ;
	void BreakAI();
	bool EnableTickPatrol = true;
	bool EnableTickMove = true;

	//	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);
	//	TArray<FVector> SearchPath(const FVector& location);
	void GoMoveActor(AActor* ToActor);
	void GoMoveLocation(FVector Location);
	TArray<AActor*> ActorsArray;
	/**** Patrol *****/
	bool LocationStartAndFinish;
	// ControllerLocation - This is where we have clicke the mouse
	// CurrentLocation - Current location  the character
	//	void SendPatrolToRepeat(AActor* CharacterSingleFVector, FVector Start, FVector Finish);
	 

	/**
	* Change position character
	* @link https://wiki.unrealengine.com/AI_Navigation_in_C%2B%2B,_Customize_Path_Following_Every_Tick
	*/
	void MoveToPositionCharacter();
	void TickPatrol();

	FVector PatrolStartLocation;
	FVector PatrolFinishLocation;
	FVector CharacterCurrentLocation;

	/**** Move Location ****/ 
	FVector SendLocation;


	bool GoMove = false;

	/**
	* add force and torque
	*/


	UFUNCTION(BlueprintCallable, Category = "AI|Navigation", meta = (WorldContext = "MoveRTS"))
		void NextPointLocation(FVector CurrentLocation, FVector FinishLocation);
	UFUNCTION(BlueprintCallable, Category = "AI|Navigation", meta = (WorldContext = "MoveRTS"))
		bool getDistancePoint();

	UFUNCTION(BlueprintCallable, Category = "AI|Navigation", meta = (WorldContext = "MoveRTS"))
		void TraceForward(FVector start_point, FVector end_point);
	//	UFUNCTION(BlueprintCallable, Category = "AI|Navigation", meta = (WorldContext = "MoveRTS"))
	//	void TraceRight(FVector start_point, FVector end_point);
	//	UFUNCTION(BlueprintCallable, Category = "AI|Navigation", meta = (WorldContext = "MoveRTS"))
	//	void TraceLeft(FVector start_point, FVector end_point);

	/*
	* Get next point to the target
	*/
	void getPointTarget(AActor* Character, FVector start_point, FVector end_point);


	TArray<FVector>  CourseOnTarget;
	FVector PointCurrentTarget;
	FVector PointCurrentAngle;
	FVector PointCurrentCameraT;
	FVector PointCurrentLocation;
	FVector PatrolPoint;
	void AddNewPoint();
	bool PatrolTarget;

	float TAngle;
	float TForce;
	float LenghtTarget;
	float RotationFloat;
	bool ThereIsPoint;
	bool PatrolGetTarget();


	//void WorkerBuildDrone(AActor* ActorWorcer, FVector Builder);

	FVector CheckPointOLD;
	float OldRange;
	float CheckRange;

private:


	UWorld * Word;
	/**
	* minimal distance
	*/
	const int32 iDistanceMin = 25;
	/**
	* max distance
	*/
	const int32 iDistanceMax = 250;


	int32 rec_log;
	int32 Finish_recursion;
	void CheckPoint();
	FVector CircumventionPoint(AActor* ToActor, FVector TargetV, float Agle, float RangeLong);

	bool CircumventionPointRange(AActor* ToActor, FVector TargetV, float Agle, float RangeLong);


	FHitResult  TracePoint_recurs(AActor* Character, FVector  Start, FVector Finish);

	FVector InFrontOfPoint(AActor* FromActor);// trace

	 


	FVector GetForwardVector(AActor* FromActor);
	//	UFUNCTION(BlueprintCallable, Category = "AI|Navigation", meta = (WorldContext = "MoveRTS"))
	void MoveForce();
	//	UFUNCTION(BlueprintCallable, Category = "AI|Navigation", meta = (WorldContext = "MoveRTS"))
	void MoveTorque();
	void _getTForse();
	void MoveActor();
	FVector PointFinish;
//	TArray<AIslandSingle*> IslandSingle;
	TArray<AActor*> ActorsToIgnore;
	TArray<AActor*> ActorsToIgnore_trace;
	FVector GetPoinAngel(FVector Center, FVector Ship, float alpha);

	TArray<FVector>  SLT(AActor* Character, FVector start_point, FVector end_point);
	FVector rotateFVector(FVector point, float angle);
	void  MoveGo();
//	void getRotationAngularActor(FRotator FRotatorActor, float currentAngular, int32 different);
};
