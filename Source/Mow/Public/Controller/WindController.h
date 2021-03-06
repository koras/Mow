// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Mow.h" 
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "BaseCharacter.h" 
#include "BaseBuilding.h"

#include "WindComponent.h"

#include "WindController.generated.h"
/* 
USTRUCT()
struct FCharacterMove
{
	GENERATED_USTRUCT_BODY()

	ABaseCharacter* ActorCharacter;
	//	float Distance;
	FVector location;
	bool BusyPoint;
	TArray<int*> PointTriangle;
};
 
USTRUCT()
struct FSinCos
{
	GENERATED_USTRUCT_BODY()
		TArray<FVector2D> location;
	//default properties
	FSinCos()
	{
		location.Add(FVector2D(0.f, 1.f));		// 0 
		location.Add(FVector2D(0.86f, 0.5f));	// 60 
		location.Add(FVector2D(0.86f, -0.5f));	//120
		location.Add(FVector2D(0.f, -1.f));		//180
		location.Add(FVector2D(-0.866f, -0.5f)); //240
		location.Add(FVector2D(-0.866f, 0.5f)); //240
	}
};
*/
USTRUCT()
struct FBusyPoint
{
	GENERATED_USTRUCT_BODY()
		FVector2D Coord;
	int NumPoint;
	int Drade;
	bool Ibusy;
};

USTRUCT()
struct FNeighborsPoint
{
	GENERATED_USTRUCT_BODY()
		int32 Center; // Center point
	TArray<int32> Neighbors;
	TArray<FVector2D> Coord;
	FVector2D CoordCenter;
};


 
UCLASS()
class MOW_API AWindController : public APlayerController
{
	GENERATED_BODY()
public:
	AWindController();
	/*
	// get all name 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BilderStuct")
		TArray<FBilderName>  BilderArrayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
		TArray<AMotionLand*> MotionLand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
		AMotionLand* SingleLand;
	AMotionLand* tmp_SingleLand;
	// All bilder name structure
	AStrategyBuilding *BaseBilder;
	AManagement* Camera;ightActionSto
	// tMouseSto
	AStrategyBuilding * SpawnBilder; 
	AIslandSingle * Island;
	*/

	UWindComponent * wComponent;
	   

	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// by pressing the left mouse button
	void LeftMouseStart();
	// When the mouse button is pressed
	void LeftMouseStop();


 
	void RightActionMouse();
	void RightActionStop();

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player, HUD and UI")
	//	TSubclassOf<class UInventoryUserWidget> InventoryUIClass;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller")
	//int32 EventUnit; // not used, renamed

	/**
	* current state
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller")
	int32 iStateController;

	bool test;
	bool test2;


 

	


	//We get all objects that are allocated by
	void GetBoxMouseCursor();
 

	void RightActionMouseIsland();

	// Set Tile of HUD
	void traceIsland(FVector Start);
	bool traceGarbage(FVector Start);
	// To determine whether a key is pressed

//	UPROPERTY(EditAnywhere, Category = "", BlueprintReadWrite)
	 

	// You can build a building or not, when choosing. 

	// players controls

	void LogicAI();  
	void SelectedBuilder();
	//void CreateNewBilder();    

	void SetCommandSpawnDrone();
	TArray<AActor*> WorldActorArray;
	 
//
//	UFUNCTION(BlueprintCallable, Category = "WidgetVariables")
	//	void ChoiceBuildingPoint();


	UFUNCTION(BlueprintCallable, Category = "WidgetVariables")
		void CenselHeroIsBuilding();
	 

	//FCharacterMove BaseCharacterStructure;
	//  BaseCharacterStructure;
	 
	TArray<FBusyPoint> ArrayBusyPoint;
	TArray<FNeighborsPoint>  ArrayNeighbors;
	FNeighborsPoint  INeighbors;

	void NewLocation();
	 
	 // Camera
	 
	TArray<AActor*> CameraArray; 
	 
	//The player is instructed to find an island to take on board the ship
	

	UFUNCTION(BlueprintCallable, Category = "Island boarding")
		void BehindTheIslandBoarded();
	
	//Take the island to abardage
	
	void SetActorLocationAbordageIsland();

	 
	// Island follows the hero
	

	void IslandFollowsTheHero();

	// mouse coordinates
	FVector MouseStartClick;
	FVector MouseFinishClick;
	FVector BoxStart;
	FVector BoxFinish;
	FVector BoxUp;
	FVector BoxDown;
	FVector BoxRight;
	FVector BoxLeft;
	//  the height at which the drawn box

	const float MouseZ = 150.0f;
	// camera move location



	FVector  BoxRadius;
	TArray< TEnumAsByte<EObjectTypeQuery> > ObjectTypes;
	TArray<FHitResult>  OutHits;
	TArray<AActor*> ActorsToIgnore;


	ABaseCharacter*  BaseCharacter;
	//ABaseCharacter*  BaseCharacterTimer; // ��� ����������� 


	FRotator Orientation;


	// set new location actor
	bool ChoosenSpawnActor;
	 

	 


	// trace
 

	// choosen heroes 


	//Only for sorting
	TArray<ABaseCharacter*> SortCharac; 
	 
	  

 
//	void SetNewBuilder(); 
	////UPROPERTY(EditAnywhere, Category = "HeroesName", BlueprintReadWrite) 
	//	bool NotChangeHud;

	UPROPERTY(EditAnywhere, Category = "Bilder", BlueprintReadWrite)
		FString BilderName = "None";

	UPROPERTY(EditAnywhere, Category = "Bilder", BlueprintReadWrite)
		bool  CreateBilder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bilder")
		float Home_location;

	 


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Island")
		bool GetIslandAbordage = false;

 
	//UFUNCTION(BlueprintCallable, Category = "Bot AI")
	//	void PatrolGO();
	 
	void GetAllMyHero();


	void CursorOverOut();
	 
	//	ALastGameMode* gms;
	 
	bool MoveActorIsland;

	bool SetNewBilder();
	//void TickUnitToForBilder();
	// Called when the game starts or when spawned 

	FColor color = FColor(200, 200, 200);

 
	void SetNewLocationBuilderAbordage();


	void  AWindController::SortCharacter(TArray<ABaseCharacter*> tmpCharacter);
	//TArray<FCharacterMove> AWindController::SortCharacter(TArray<FCharacterMove> TArCharacterStructure);

//	void SortCharacter();
	//	void GetPointLocation();
	//void CobeShip(); 

	 
	//	UFUNCTION(BlueprintCallable, Category = "Build Stractions")
	//	bool BuildStractions(int32 iBuild);


	UFUNCTION(BlueprintCallable, Category = "Build Stractions")
		bool BuildStractionName(int32 iBuildName);

	 
	 
	 

	TArray<int*> Point;
 
	int32 Arm;


	FVector GetPointCursor();

	void BattleDetectStart();
	void BattleDetectStop(); 

	void SetNewLocationBuilder();
	//void SetNewLocationHeroes();
	void SetActorLocationBilder();
	void SetActorLocationHeroes();


	bool BuildBreak();
	bool HeroesBreak(); 

	void SpawnCursorPoint();
private:
	void __MouseClickMoveChar(ABaseCharacter* ObjCharacter);
	void ClearVar();
	bool Production = true;

	//  Making HUD change available
	// HUD makes available a change 

	bool youCanBuildDrone = false;

	//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "trace")
	float ZCamera = 52.f;
	//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "trace")
	float  ZCursor = 2000.f;
	//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "trace")
	float  XCamera = -10.f;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "trace")
	float  XEnd = 560.f;
	//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "trace")
	float  proc = -62;
	//	void SpawnCursorPoint(); 
	 

	 

	//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Build")
	bool BuildViewportCanvas = false;
	//SpawnNewBilderLocation
	// search new location for builder
	// search for a new location for the building
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Build")
		//bool SpawnNewBilderLocation = false;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Heroes")
		bool SpawnNewHeroesLocation = false;




	bool bBattleVector = false;
	bool bBattleCursor = false;


//
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
		FVector PatrolLocationStart;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
		FVector PatrolLocationEnd;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
	//	bool isPatrol = false;
		bool bEnableMouseOverEvents = true;
		bool bShowMouseCursor = true; 
		bool bPressRightMouseKey = false;
		bool SpawnDrone = false;
};
