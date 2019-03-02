// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "Logic.h"
#include "GameFramework/NavMovementComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
 
#include "Runtime/Engine/Classes/AI/NavigationSystemBase.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h" 
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"

#include "Runtime/NavigationSystem/Public/NavigationSystem.h"  
#include "Runtime/NavigationSystem/Public/NavigationPath.h"


#include "AI/Navigation/NavigationTypes.h"
//#include "AI/Navigation/NavigationData.h"

  

#include "BaseLand.h"
#include "BaseCharacter.h" 

#include "ShipNavMovementComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MOW_API UShipNavMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:

	UShipNavMovementComponent();

		bool debug = false;
		 

	// Called every frame
//	virtual void Tick(float DeltaSeconds) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Current which will manage
	AActor* ToActorCharacter;
	AActor* Character;

	//	ABaseCharacter*  Character;

	UPrimitiveComponent * PrimitivePawn;



	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	Logic* ALogic;
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

	void SendPatrolTo(UPrimitiveComponent * Primitive, AActor* BaseCharacter, FVector Finish);

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
	void SendMoveActor(UPrimitiveComponent * Primitive, AActor* CharacterSingleFVector, FVector FinishLocation);
	FVector SendLocation;


	bool GoMove = false;

	/**
	* add force and torque
	*/
	UNavigationSystemV1* navSys;

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
	//void CheckPoint();

private:

	/**
	* minimal distance
	*/
	const int32 iDistanceMin = 25;
	/**
	* ћаксимальна€ дистанци€ до цели дл€ прокладки пути
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
	bool TracePoint(AActor* ActorIgnor, FVector Start, FVector Finish);
	FVector GetForwardVector(AActor* FromActor);
	//	UFUNCTION(BlueprintCallable, Category = "AI|Navigation", meta = (WorldContext = "MoveRTS"))
	void MoveForce();
	//	UFUNCTION(BlueprintCallable, Category = "AI|Navigation", meta = (WorldContext = "MoveRTS"))
	void MoveTorque();
	void _getTForse();
	void MoveActor();
	FVector PointFinish;
	TArray<ABaseLand*> IslandSingle;
	TArray<AActor*> ActorsToIgnore;
	TArray<AActor*> ActorsToIgnore_trace;
	FVector GetPoinAngel(FVector Center, FVector Ship, float alpha);

	TArray<FVector>  SLT(AActor* Character, FVector start_point, FVector end_point);
	FVector rotateFVector(FVector point, float angle);
	void  MoveGo();
	void getRotationAngularActor(FRotator FRotatorActor, float currentAngular, int32 different);
};
