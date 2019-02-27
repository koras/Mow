// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseCharacter.h" 
#include "BaseBuilding.h"
 


#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Engine/Public/EngineUtils.h"



#include "WindComponent.generated.h"

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

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MOW_API UWindComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWindComponent();

	FVector TMP_location; // saving coordinates

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void CobeShip(FVector vLocation, TArray<FCharacterMove> Characters);
	void SortCharacter();

	TArray<FCharacterMove> TArCharacterStructure;

	FCharacterMove BaseCharacterStructure;

	void GetBoxMouseCursor(APlayerController* PlayerController);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
		TArray<ABaseCharacter*> HUDCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Island")
		bool ChangeHeroes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
		TArray<ABaseCharacter*> Charac;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character for AI")
		TArray<ABaseCharacter*>BaseCharacterMyHero;

	UPROPERTY(EditAnywhere, Category = "Character", BlueprintReadWrite)
		bool  MouseSelectedHUD = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
		bool isPatrol = false;

	void SelectedCharacter(APlayerController* PlayerController);
 
	void Server_DefaultMouseClick();
	bool MyHeroBranch = false;

	bool bPressRightMouseKey = false;

	void SetNewLocationBuilder();


	/**
	* Client search Garbage
	* Search for island installations building
	*/
	void SetActorLocationHeroes(APlayerController* PlayerController);
	void PatrolGO(APlayerController* PlayerController);

	void SetNewLocationBuilderAbordage();

	bool  NotChangeHud = true;
	ABaseCharacter*  BaseCharacterTimer; // 


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bilder")
		bool BuilderBarrakActive = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Build")
	bool SpawnNewBilderLocation = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Heroes")
	bool SpawnNewHeroesLocation = false;

	ABaseBuilding * iMeshBuilder;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Build")
		ABaseBuilding * BuildController;


	bool BuildBreak();

	ABaseCharacter*  iBaseCharacterSpawn;

	bool bWindYouCanBuild = false;

	bool  traceGarbage(FVector Start);

	void  ChoiceBuildingPoint(APlayerController* PlayerController);

	void LogicAI(APlayerController* PlayerController);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Build")
		int32 iBuildStrange = 0;
private: 

	void CenselHeroIsBuilding();

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Build")
 

	ABaseLand * SingleLand;
	ABaseLand * tmp_SingleLand;

	FRotator Orientation;

	TArray<AActor*> ActorsToIgnore;
	FVector  BoxRadius;
	TArray< TEnumAsByte<EObjectTypeQuery> > ObjectTypes;
	TArray<FHitResult>  OutHits;

	const float MouseZ = 150.0f;

	FVector BoxStart;
	FVector BoxFinish;
	FVector BoxUp;
	FVector BoxDown;
	FVector BoxRight;
	FVector BoxLeft;
	//FSinCos SinCos;
	float DistanceRangePoint = 300.f;

	void __MouseClickMoveChar(ABaseCharacter* ObjCharacter);
	 

	 
};
