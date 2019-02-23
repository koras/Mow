// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Mow.h"

#include "GameFramework/Pawn.h"

#include "Components/SphereComponent.h" 
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Components/AttributesComponent.h"
#include "ConstructorHelpers.h" 
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include "Runtime/Engine/Classes/Engine/SkeletalMesh.h"

#include "Island/BaseLand.h"

#include "BaseCharacter.generated.h" 



USTRUCT()
struct FCharacterTile
{
	GENERATED_USTRUCT_BODY()

		//Vars
		int32 	number;// number tile
	FString		toolTip;// name tile
	FString		ButtonType; // type tile
//	UTexture2D* TexturePressed;
//	UTexture2D* TextureReleased;

	float 		minX;
	float 		maxX;
	float 		minY;
	float 		maxY;


	//default properties

	FCharacterTile()
	{
		//	static ConstructorHelpers::FObjectFinder<UTexture2D> ButtonBack(TEXT("/Game/HUD/Texture/Texture_red_yellow.Texture_red_yellow"));
		//	static ConstructorHelpers::FObjectFinder<UTexture2D> EnemyTeamHPObj(TEXT("/Game/HUD/Texture/blue.blue"));
		number = 1;
		toolTip = "";
		ButtonType = "";
		//	TexturePressed = ButtonBack.Object;
		//	TextureReleased = EnemyTeamHPObj.Object;
		minX = 0;
		maxX = 50;
		minY = 0;
		maxY = 50;

	}
};





UCLASS()
class MOW_API ABaseCharacter : public APawn
{
	GENERATED_UCLASS_BODY()

public:
	// Sets default values for this pawn's properties
	//ABaseCharacter();

	bool test1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle")
		UAttributesComponent *Attributes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent * WeaponMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent * WeaponMeshClick;



	UPROPERTY(EditAnywhere, Category = "Heroes", BlueprintReadWrite)
		int32 ClanChar;
	/*
	* We go to the island to take the island
	*/
	UPROPERTY(EditAnywhere, Category = "Island boarding", BlueprintReadWrite)
		bool GoBehindTheIsland;
	/*в
	* We go to the island to take the island
	*/
	UPROPERTY(EditAnywhere, Category = "Island boarding", BlueprintReadWrite)
		bool SelectEraseToBoarding;
	/*
	* Ищем остров для абордажа
	* We are looking for an island boarding
	*/
	UPROPERTY(EditAnywhere, Category = "Island boarding", BlueprintReadWrite)
		bool SearchIslandForAbordage;
	/*
	* Имеет ли права герой тоскать острова
	* Does the right to carry the hero of the island
	*/
	UPROPERTY(EditAnywhere, Category = "Island boarding", BlueprintReadWrite)
		bool RightHeroOfTheIsland;

	UPROPERTY(EditAnywhere, Category = "Mesh", BlueprintReadWrite)
		USphereComponent* proxSphere;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anims")
		USkeletalMeshComponent *IslandSkeletalMeshMesh;


	/*my hero or foe*/
	UPROPERTY(EditAnywhere, Category = "Hero property", BlueprintReadWrite)
		bool MyHero;


	UPROPERTY(EditAnywhere, Category = "HeroesName", BlueprintReadWrite)
		FString NameCurrentHeroes;

	void BreakCommand();

	//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		//	UAudioComponent* AudioComponentDead;
		//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		//	UAudioComponent* AudioComponentCannon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle")
		bool bBattleSelectedCursor;


	UPROPERTY(EditAnywhere, Category = "Controller", BlueprintReadWrite)
		bool MouseEvent;


	//	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HUD")
	//		UUserWidget * DataBar;
	//	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HUD")
	//		UUserWidget * DataBar_delete;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(Category = Default)
		void OnClick(UPrimitiveComponent* pComponent);
	UFUNCTION(Category = Default)
		void CursorOver(UPrimitiveComponent* pComponent);
	UFUNCTION(Category = Default)
		void CursorOut(UPrimitiveComponent* pComponent);

	// Уровень бога
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "God")
		bool iGod;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		UAudioComponent* AudioComponentDead;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		UAudioComponent* AudioComponentCannon;

	float  TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)  override;


	UMaterialInterface * StoredMaterial;

 
public:

	/* PATROL
	* Server
	*/
	UFUNCTION(Server, Reliable, WithValidation)
		void Server_PatrolToTepeat(FVector ControllerLocation);


	UPROPERTY(EditAnywhere, Category = "IsLand", BlueprintReadWrite)
		ABaseLand* tpm_IsLand;

	UPROPERTY(EditAnywhere, Category = "IsLand", BlueprintReadWrite)
		ABaseLand* IsLand;

	UPROPERTY(Replicated, EditAnywhere, Category = "Build")
		bool bCanBuildIsland;

	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	//	UPROPERTY(EditAnywhere, Category = "Island boarding", BlueprintReadWrite)
	//	bool PossibleToBoardTheIsland;

	UPROPERTY(EditAnywhere, Category = "Island boarding", BlueprintReadWrite)
		UPhysicsConstraintComponent* ConstraintComp;



	UFUNCTION(BlueprintCallable, Category = "WidgetVariables")
		int32 GetScore();
	UFUNCTION(BlueprintCallable, Category = "WidgetVariables")
		FString HeroesName();
	UFUNCTION(BlueprintCallable, Category = "Island boarding")
		void RemovingIslandAbordage();

	//UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Anims")
	//	UBlendSpace1D *BlendSpace;

	//UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Anims")
	//	UBlendSpace *BS;
	// property




	void AddTimeHealth();

	UPROPERTY(EditAnywhere, Category = "Hero property", BlueprintReadWrite)
		bool bBusy;
	UFUNCTION(BlueprintCallable, Category = "move")
		void SetNewLocation(FVector DestLocation);
	/*
	* Может ли герой двигаться
	* Can the hero to move
	*/
	UPROPERTY(Replicated, EditAnywhere, Category = "Move")
		bool CharacterMove;

	// Заблокирована или нет кнопка поиска островка
	UPROPERTY(EditAnywhere, Category = "Island boarding", BlueprintReadWrite)
		bool HUDabordage;

	UPROPERTY(EditAnywhere, Category = "Island boarding", BlueprintReadWrite)
		bool bIsAbordage;

	//void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const;

	/*my hero or foe*/
	UPROPERTY(EditAnywhere, Category = "Hero property", BlueprintReadWrite)
		int32 HeroFraction;


	void FollowTheIslandFunction();


	UPROPERTY(EditAnywhere, Category = "Health", BlueprintReadWrite)
		bool FollowTheActor;


	virtual void ChangeColorGood();
	virtual void ChangeColorWarning();
	virtual void ChangeColorDefault();
	virtual void ChangeColorReserved();
	virtual void ChangeColorReservedGood();
	virtual void BuildCharacter();
	virtual void WhobuildsBuilding();
	virtual void ClickCharacter();
	bool bBuild;

private:


	// Двигаемся к острову на абордаж
	bool bIsLandBoarding;
	bool bConstraintComp;

	void DeadActorMagic();
	void DeadActor();
	void SpawnGarbage();
	void IslandSearch();

	FVector vTmp;  
	void HealthComputation();

	FVector fvbDroneFVector; /** местоположение дрона */
	bool bCanBuilder;
	bool bGoInDrone;

	void GoBuildDrone(); /** tick */
	 

	 
	 
	 
};




