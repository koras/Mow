// Fill out your copyright notice in the Description page of Project Settings.

#include "Worker.h"

AWorker::AWorker(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

	static ConstructorHelpers::FObjectFinder <UStaticMesh>StaticMesh(TEXT("StaticMesh'/Game/Heroes/WorkerH/mesh/Worker_v5.Worker_v5'"));
	check(StaticMesh.Object);
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Material_Island_tmp(TEXT("MaterialInstanceConstant'/Game/Heroes/WorkerH/mat/worker_texturing3_Mat_Inst.worker_texturing3_Mat_Inst'"));
	check(Material_Island_tmp.Object);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> bone(TEXT("SkeletalMesh'/Game/Heroes/WorkerH/anim/idle/Worker_idle.Worker_idle'"));
	check(bone.Object);
 

	WeaponMesh->SetStaticMesh(StaticMesh.Object);
	WeaponMesh->SetMaterial(0, Material_Island_tmp.Object);

	IslandSkeletalMeshMesh->SetSkeletalMesh(bone.Object);
	IslandSkeletalMeshMesh->SetMaterial(0, Material_Island_tmp.Object);
 
 
}

// Called when the game starts or when spawned
void AWorker::BeginPlay()
{
	Super::BeginPlay();
}

void AWorker::OverlapBeginComponent(UPrimitiveComponent* OverlappedComp)
{
	//	UE_LOG(LogTemp, Warning, TEXT("AWorkerH::OverlapBeginComponent OverlapBeginComponent 777"));

}

void AWorker::AnimationGo()
{
	//	UE_LOG(LogTemp, Warning, TEXT("AWorkerH::AnimationGo()"));
	FVector BlendParams(.0f, 0.0f, 0.0f);
	//IslandSkeletalMeshMesh->PlayAnimation(BlendSpace, true);
	//IslandSkeletalMeshMesh->GetSingleNodeInstance()->SetBlendSpaceInput(BlendParams);
}




void AWorker::AnimationSTOP()
{
 
}

void AWorker::AnimationStart()
{

}
// Called every frame
void AWorker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

 
}

void AWorker::NativeInitializeAnimation()
{
}
void AWorker::NativeUpdateAnimation(float DeltaTimeX)
{
}

void AWorker::GoBuild()
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