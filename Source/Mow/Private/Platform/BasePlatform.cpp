// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePlatform.h"

// Sets default values
ABasePlatform::ABasePlatform(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	UE_LOG(LogTemp, Warning, TEXT("ABasePlatform::ABasePlatform 1"));

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder <UStaticMesh>StaticMesh(TEXT("StaticMesh'/Game/Platform/Platform.Platform'"));
	//	static ConstructorHelpers::FObjectFinder <UMaterial> Material(TEXT("Material'/Game/Platform/Material/Metal_CyberCube.Metal_CyberCube'"));

	Fly = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SolidBlock"));

	//	Fly->AttachTo(RootComponent);
	Fly->SetStaticMesh(StaticMesh.Object);
	FVector Scale = FVector(40.0f, 40.0f, 0.001f);
	Fly->CastShadow = false;
	Fly->SetWorldScale3D(Scale);
//	Fly->SetMobility(EComponentMobility::Static);
}

// Called when the game starts or when spawned
void ABasePlatform::BeginPlay()
{
	Super::BeginPlay();
	 
}

// Called every frame
//void ABasePlatform::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);

//}

// Called to bind functionality to input
void ABasePlatform::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

