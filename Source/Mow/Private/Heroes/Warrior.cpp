// Fill out your copyright notice in the Description page of Project Settings.

#include "Warrior.h"


AWarrior::AWarrior(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder <UStaticMesh>StaticMesh(TEXT("StaticMesh'/Game/Heroes/WarriorH/v3/warrior.warrior'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material_Island_tmp(TEXT("MaterialInstanceConstant'/Game/Heroes/WarriorH/v3/Warrior2_Inst.Warrior2_Inst'"));


	check(StaticMesh.Object);
	check(Material_Island_tmp.Object);
	StoredMaterial = Material_Island_tmp.Object;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> bone(TEXT("SkeletalMesh'/Game/Heroes/WarriorH/anim/warrior_idle.warrior_idle'"));
	check(bone.Object);



	WeaponMesh->SetStaticMesh(StaticMesh.Object);
	WeaponMesh->SetMaterial(0, StoredMaterial);

	IslandSkeletalMeshMesh->SetSkeletalMesh(bone.Object);
	IslandSkeletalMeshMesh->SetMaterial(0, StoredMaterial);


}

// Called when the game starts or when spawned
void AWarrior::BeginPlay()
{
	Super::BeginPlay();
}

void AWarrior::OverlapBeginComponent(UPrimitiveComponent* OverlappedComp)
{
	//	UE_LOG(LogTemp, Warning, TEXT("AWorkerH::OverlapBeginComponent OverlapBeginComponent 777"));

}

void AWarrior::AnimationGo()
{
	//	UE_LOG(LogTemp, Warning, TEXT("AWorkerH::AnimationGo()"));
	FVector BlendParams(.0f, 0.0f, 0.0f);
	//IslandSkeletalMeshMesh->PlayAnimation(BlendSpace, true);
	//IslandSkeletalMeshMesh->GetSingleNodeInstance()->SetBlendSpaceInput(BlendParams);
}




void AWarrior::AnimationSTOP()
{

}

void AWarrior::AnimationStart()
{

}
// Called every frame
void AWarrior::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AWarrior::NativeInitializeAnimation()
{
}
void AWarrior::NativeUpdateAnimation(float DeltaTimeX)
{
}

void AWarrior::GoBuild()
{
	//	if (bBuild)
	//{
	//	//	UE_LOG(LogTemp, Warning, TEXT("AWorkerH::GoBuild() Go Builder"));
	//	if (BaseCharacter[0])
	//	{
	//		BaseCharacter[0]->isbuild = true;
	//	}
	//	}
}