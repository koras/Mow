// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h" 

// Sets default values
ABaseCharacter::ABaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Attributes = CreateDefaultSubobject<UAttributesComponent>(TEXT("Attribute"));
	//Attributes->RangeView = 1100;
	//Attributes->TimeOfShooting = 0.5f;
	//Attributes->Shoot = 1;
	//Attributes->fDamageAmount(100.f);
	//GunComponent->RegisterComponent();

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	//	UE_LOG(LogTemp, Warning, TEXT("ABaseCharacter::OnClick Кликаем по герою"));

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
	//	{// выключаем бар
	//		DataBar->RemoveFromParent();
	//	}

	//Если корабль тащит остров, то его необходимо отцепить
	RemovingIslandAbordage();
	// удаляем объект корабля из игры
	Destroy();
}

/*
*  Остров снимается с абордажа с кнопки на HUD
* или когда умирает герой
*/
void ABaseCharacter::RemovingIslandAbordage() {
	if (Attributes->bIsAbordage) {
		//	UE_LOG(LogTemp, Warning, TEXT("Герой снимает остров с абордажа"));

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
			//	UE_LOG(LogTemp, Warning, TEXT("Удаляем компонент"));
		}
	}
}



// Called to bind functionality to input
void ABaseCharacter::SetNewLocation(FVector DestLocation)
{
	/*
	if (CharacterMove) {
	if (!PlayerAI)
	{
	PlayerAI = Cast<ABaseAIController>(GetController());
	}
	if (PlayerAI)
	{
	IsMoveActor = true;
	AnimationStart();

	//	UE_LOG(LogTemp, Warning, TEXT("Новая точка движения GetActorLocation %f, %f, %f"), GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);
	//	UE_LOG(LogTemp, Warning, TEXT("Новая точка движения DestLocation %f, %f, %f"), DestLocation.X, DestLocation.Y, DestLocation.Z);
	PlayerAI->SendMoveActor(WeaponMesh, this, DestLocation);
	bBusy = true;
	}
	}
	*/
}




int32 ABaseCharacter::GetScore()
{
	return 0.0f;
}
FString ABaseCharacter::HeroesName()
{
	return NameCurrentHeroes;
}



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