// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h" 


// Sets default values
ABaseCharacter::ABaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	Attributes = CreateDefaultSubobject<UAttributesComponent>(TEXT("Attribute"));
	PrimaryActorTick.bCanEverTick = true;
	Attributes->SetMyHero(true);

	//static ConstructorHelpers::FObjectFinder<UBlendSpace1D>  BS(TEXT("BlendSpace1D'/Game/Heroes/WorkerH/anim/idle/worker_anim_Skeleton_BlendSpace1D2.worker_anim_Skeleton_BlendSpace1D2'"));
	//check(BS.Object);
	//static ConstructorHelpers::FObjectFinder <UStaticMesh>cubeStandart(TEXT("StaticMesh'/Game/Primitive/mash/cubeStandart.cubeStandart'"));
	//check(cubeStandart.Object);
	static ConstructorHelpers::FObjectFinder <UStaticMesh>ObodMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	check(ObodMesh.Object);
//	static ConstructorHelpers::FObjectFinder <UStaticMesh>ObodMesh2(TEXT("StaticMesh'/Game/Primitive/mash/cube2.cube2'"));
	//check(ObodMesh.Object);
//	BlendSpace = BS.Object;



	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT("Block"));
	RootComponent = WeaponMesh;

	WeaponMesh->CastShadow = false;
	WeaponMesh->bVisible = false;
	WeaponMesh->SetWorldScale3D(FVector(1.f));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	WeaponMesh->SetCollisionProfileName(FName("WarrCharacter"));

	WeaponMesh->SetConstraintMode(EDOFMode::XYPlane);
	//WeaponMesh->OnClicked.AddDynamic(this, &ABaseCharacter::OnClick);
	////WeaponMesh->OnBeginCursorOver.AddDynamic(this, &ABaseCharacter::CursorOver);
	//WeaponMesh->OnEndCursorOver.AddDynamic(this, &ABaseCharacter::CursorOut);
	//WeaponMesh->SetLinearDamping(powerMotion);
	//WeaponMesh->SetAngularDamping(angularRotation);
	WeaponMesh->SetSimulatePhysics(true);





	// FOR COLLISION
	proxSphere = CreateDefaultSubobject<USphereComponent>( TEXT("Sphere"));
//	proxSphere->AttachTo(RootComponent);
	proxSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	proxSphere->SetSphereRadius(80.f);// old 40
	proxSphere->SetRelativeLocation(FVector(0.0f, 0.0f, 150.0f));
	proxSphere->SetCollisionProfileName(FName("WarrCircle"));


	// IslandSkeletalMeshMesh
	IslandSkeletalMeshMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("IslandSkeletalMeshMesh"));
	//IslandSkeletalMeshMesh->AttachTo(RootComponent);
	IslandSkeletalMeshMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform); 
	IslandSkeletalMeshMesh->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
//	IslandSkeletalMeshMesh->SetMaterial(0, Material_Island_tmp.Object);
	IslandSkeletalMeshMesh->SetCollisionProfileName(FName("OverlapAll"));
	IslandSkeletalMeshMesh->CastShadow = false;
//	IslandSkeletalMeshMesh->SetAnimationMode(EAnimationMode::AnimationSingleNode);

//	FPushForceModule* const MovePlugin = FModuleManager::LoadModulePtr<FPushForceModule>("MyModule");

//	MovePlugin = FModuleManager::LoadModulePtr<FPushForceModule>("MyModule");
//MovePlugin = CreateDefaultSubobject<FPushForceModule>(TEXT("MyPluginComponent"));
}





// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupInputComponent();
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ABaseCharacter::CursorOver(UPrimitiveComponent* pComponent)
{
	MouseEvent = true;
	//	if (DataBar) {

	//	DataBar->SetVisibility(ESlateVisibility::Visible);
	//	UE_LOG(LogTemp, Warning, TEXT("ABaseCharacter::CursorOver 1"));
	//	}
	//	 UE_LOG(LogTemp, Warning, TEXT("ABaseCharacter::CursorOver 2"));

}
void ABaseCharacter::CursorOut(UPrimitiveComponent* pComponent)
{
	MouseEvent = false;
	//	if (DataBar) {
	//	DataBar->SetVisibility(ESlateVisibility::Hidden);
	//		UE_LOG(LogTemp, Warning, TEXT("ABaseCharacter::CursorOut 1"));
	//	}
}

void ABaseCharacter::OnClick(UPrimitiveComponent* pComponent)
{

}





// This is the actor damage handler.    DataBar
float ABaseCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	if (iGod)
	{
		//	UE_LOG(LogTemp, Warning, TEXT("i God %f"), Damage);
		return Damage;
	}


	// Call the base class - this will tell us how much damage to apply  
	const float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	if (ActualDamage > 0.f)
	{

		//	UE_LOG(LogTemp, Warning, TEXT("Damage-> %f %f %f"), CharacterCurrentHealth, Damage, ActualDamage);
		Attributes->SetHealth(ActualDamage * (-1)); //-= ActualDamage;
													//	UE_LOG(LogTemp, Warning, TEXT("CharacterCurrentHealth %f"), CharacterCurrentHealth);
													// If the damage depletes our health set our lifespan to zero - which will destroy the actor  
		if (Attributes->GetHealth() <= 0.f)
		{
			Attributes->SetHealth(0);
			//		UE_LOG(LogTemp, Warning, TEXT("SetLifeSpan(0.001f);"));
			//	SetLifeSpan(0.001f);
			// dead
			DeadActorMagic();
		}
		else {
			if (AudioComponentCannon)AudioComponentCannon->Play();
		}
	}
	//  DataBar
	//	UE_LOG(LogTemp, Warning, TEXT("ActualDamage %f"), ActualDamage);
	return ActualDamage;
}



//void ABaseCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//UE_LOG(LogTemp, Warning, TEXT("Replicated"));
// Replicate to everyone
//	DOREPLIFETIME(ABaseCharacter, CharacterMove);
//	DOREPLIFETIME(ABaseCharacter, BaseCharLocation);
//}



void ABaseCharacter::DeadActorMagic()
{
	//	UE_LOG(LogTemp, Warning, TEXT(" magic actor "));
	// magic actor 
	//	SpawnGarbage();
	//	DeadActor();
}



void ABaseCharacter::DeadActor()
{
	//CheckerHeroes->Destroy();
	//	if (PlayerAI)
	//	{ 
	//	PlayerAI->Destroy();
	//}

	//	if (DataBar)
	//	{
	//		DataBar->RemoveFromParent();
	//	}

	RemovingIslandAbordage();
	Destroy();
}

void ABaseCharacter::RemovingIslandAbordage() {
	if (Attributes->bIsAbordage) {
		if (ConstraintComp)
		{
			ConstraintComp->RemoveFromRoot();
			ConstraintComp->BreakConstraint();
			ConstraintComp->DestroyComponent(true);
			HUDabordage = false;
			SelectEraseToBoarding = false;
			bConstraintComp = true;
			bIsLandBoarding = true;

			Attributes->bIsAbordage = false;

			//	IsLand->BreackAbordage();
			//IsLand->bHeroes_Island = false;
			bBusy = false;

			SetNewLocation(GetActorLocation() + GetActorForwardVector()*300.f);
		}
	}
}



// Called to bind functionality to input
void ABaseCharacter::SetNewLocation(FVector DestLocation)
{

	// 	UE_LOG(LogTemp, Warning, TEXT("Move->IsThisNumber42 %f") , MovePlugin->IsThisNumber42());

		//MovePlugin->StartupModule();
		 
		//MovePlugin->SendMoveActor(WeaponMesh, this, DestLocation);

		UE_LOG(LogTemp, Warning, TEXT("new location ABaseCharacter::SetNewLocation %f %f "), DestLocation.X, DestLocation.Y);
  
	if (CharacterMove) {
	
	if (!PlayerAI)
	{
	PlayerAI = Cast<ABaseAIController>(GetController());
	}
	if (PlayerAI)
	IsMoveActor = true;
	AnimationStart();

	//	UE_LOG(LogTemp, Warning, TEXT(" GetActorLocation %f, %f, %f"), GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);
	//	UE_LOG(LogTemp, Warning, TEXT("DestLocation %f, %f, %f"), DestLocation.X, DestLocation.Y, DestLocation.Z);
	PlayerAI->SendMoveActor(WeaponMesh, this, DestLocation);
	bBusy = true;
	
	
	}
	 
}


/*

int32 ABaseCharacter::GetScore()
{
	return 0.0f;
}
FString ABaseCharacter::HeroesName()
{
	return NameCurrentHeroes;
}
*/


////void ABaseCharacter::AddTimeHealth()
//{
//SetHealth(CharacterAddHealth);
//}
/*
void ABaseCharacter::SetHealth(float Healt) {
CharacterCurrentHealth += Healt;
if (CharacterCurrentHealth >= CharacterMaxHealth)CharacterCurrentHealth = CharacterMaxHealth;

//	UE_LOG(LogTemp, Warning, TEXT("CharacterCurrentHealth %f"), CharacterCurrentHealth);
}
*/
void ABaseCharacter::BreakCommand()
{
//	PlayerAI = Cast<ABaseAIController>(GetController());
//	if (PlayerAI) {

		bBusy = false;
	//	PlayerAI->BreakAI();
//	}
}




void ABaseCharacter::Server_PatrolToTepeat_Implementation(FVector ControllerLocation)
//void ABaseCharacter::Server_PatrolToTepeat(FVector ControllerLocation)
{
//	UE_LOG(LogTemp, Warning, TEXT("Move->IsThisNumber42 %f "), Move->IsThisNumber42(25)); 
	 
/* 
	//	UE_LOG(LogTemp, Warning, TEXT("ABaseCharacter::Server_PatrolToTepeat_Implementation"));
	if (!PlayerAI)
	{
		PlayerAI = Cast<ABaseAIController>(GetController());
	}

	if (PlayerAI)
	{
		PlayerAI->SendPatrolTo(WeaponMesh, this, ControllerLocation);
		//	UE_LOG(LogTemp, Warning, TEXT("PlayerAI true Patrol %f %f"), ControllerLocation.X, ControllerLocation.Y);
	}
	else {
		//	UE_LOG(LogTemp, Warning, TEXT("PlayerAI false Patrol"));
	}
	*/
}
bool ABaseCharacter::Server_PatrolToTepeat_Validate(FVector ControllerLocation)
{
	return true;
}


/**
* Hero get information on building construction 
*/
void ABaseCharacter::FollowTheIslandFunction()
{
	if (IsLand)
	{
		FollowTheActor = true;
	}
}



void ABaseCharacter::ChangeColorGood() {}
void ABaseCharacter::ChangeColorWarning() {}
void ABaseCharacter::ChangeColorDefault() {}
void ABaseCharacter::ChangeColorReserved() {}
void ABaseCharacter::ChangeColorReservedGood() {}

void ABaseCharacter::ClickCharacter() {}
void ABaseCharacter::BuildCharacter() {}

void ABaseCharacter::WhobuildsBuilding() {}

void ABaseCharacter::HealthComputation()
{
	const int32 GoFire = 45; 
	//float procent = CharacterCurrentHealth / (CharacterMaxHealth / 100);
	////	UE_LOG(LogTemp, Warning, TEXT("Fire: %f %f %f"), CharacterMaxHealth, procent, CharacterCurrentHealth);

	if(Attributes->GetCurrentProcent() < GoFire)
		{
		FireActive();
	}
	else
	{
		FireDeActive();
	}
}


void ABaseCharacter::FireActive()
{
	//	UE_LOG(LogTemp, Warning, TEXT("AWarrior::FireActive()"));
	if (ParticleEffectFire)
	{
		//	UE_LOG(LogTemp, Warning, TEXT("AWarrior::FireActive() 2"));
	//	ParticleEffectFire->Deactivate();
	//	ParticleEffectFire->Activate();
	}
}

void ABaseCharacter::FireDeActive()
{
	if (ParticleEffectFire)
	{
	//	//	UE_LOG(LogTemp, Warning, TEXT("AWarrior::FireDeActive() 2"));
	//	ParticleEffectFire->Deactivate();
	}
}


/**
* For demo
*/

void ABaseCharacter::IslandSearch()
{
	for (TActorIterator<ABaseLand> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ABaseLand *Island = *ActorItr;
		if (Island->Attributes->GetFraction() == this->Attributes->GetFraction())
		{
			FVector IslandLoc = Island->GetActorLocation();
			SetNewLocation(IslandLoc);
			return;
		}
	}
}
