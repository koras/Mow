// Fill out your copyright notice in the Description page of Project Settings.

#include "WindComponent.h"

// Sets default values for this component's properties
UWindComponent::UWindComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWindComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UWindComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



// sort ship
void   UWindComponent::CobeShip(FVector vLocation, TArray<FCharacterMove> Characters) {

	FVector2D CoordShip = FVector2D(vLocation.X, vLocation.Y);
	FVector2D NewCoordShip = FVector2D(vLocation.X, vLocation.Y);
	bool residue = false;
	int32 CountShipSum = Characters.Num();

	if (CountShipSum == 1) {
		Characters[0].location = FVector(vLocation.X, vLocation.Y, 150.f);
	}
	const int LineShip = FMath::Sqrt(CountShipSum);
	int32 ResidueShips = 0;
	if (LineShip*LineShip != CountShipSum)
	{
		ResidueShips = CountShipSum - LineShip*LineShip;
	}

	NewCoordShip.X = CoordShip.X - (LineShip * DistanceRangePoint / 2);
	NewCoordShip.Y = CoordShip.Y - (LineShip * DistanceRangePoint / 2);

	//UE_LOG(LogTemp, Warning, TEXT("coord  %f %f %f"),  NewCoordShip.X, NewCoordShip.Y, DistanceRangePoint);
	int32 Ship = 0;
	float ShipY_tmp = NewCoordShip.Y;
	float ShipX_tmp = NewCoordShip.X;
	for (int32 IX = 0; IX != LineShip; ++IX)
	{
		NewCoordShip.X = NewCoordShip.X + DistanceRangePoint;
		NewCoordShip.Y = ShipY_tmp;  
		for (int32 IY = 0; IY != LineShip; ++IY)
		{
			NewCoordShip.Y = NewCoordShip.Y + DistanceRangePoint;
			//	UE_LOG(LogTemp, Warning, TEXT("%d %f %f %f"), Ship, NewCoordShip.X, NewCoordShip.Y, DistanceRangePoint);
			FVector data3d = FVector(NewCoordShip.X, NewCoordShip.Y, 0.f);
			TArCharacterStructure[Ship].location = data3d;
			Ship++;
		}
	}

	NewCoordShip.X = NewCoordShip.X + DistanceRangePoint;
	NewCoordShip.Y = ShipY_tmp; 
	if (ResidueShips > 0)
	{
		for (int32 IDop = 0; IDop != ResidueShips; ++IDop)
		{
			NewCoordShip.Y = NewCoordShip.Y + DistanceRangePoint;
			FVector data3d = FVector(NewCoordShip.X, NewCoordShip.Y, 150.f);
			TArCharacterStructure[Ship].location = data3d;
			Ship++;
		}
	}
}
/*
* We touch the heroes to sort from the far point to the near
*  Itteration heroes for check point
*/
void UWindComponent::SortCharacter()
{

	TArray<ABaseCharacter*> tmpCharacter = Charac;
	//UE_LOG(LogTemp, Warning, TEXT("get point Start"));
	TArCharacterStructure.Empty();
	for (int32 Index = 0; Index != tmpCharacter.Num(); ++Index)
	{
		if (tmpCharacter[Index]) {
			if (tmpCharacter[Index]->Attributes->GetMyHero())
			{
				BaseCharacterStructure.ActorCharacter = tmpCharacter[Index];
				TArCharacterStructure.Add(BaseCharacterStructure);
			}
		}
	}
	//CobeShip();
	CobeShip(TMP_location, TArCharacterStructure);
}




void UWindComponent::GetBoxMouseCursor(APlayerController* PlayerController) {

	FHitResult HitResult;

	PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

	BoxFinish = HitResult.Location;
	BoxDown.X = BoxFinish.X;
	BoxDown.Y = BoxFinish.Y;
	BoxRight.X = BoxFinish.X;
	BoxLeft.Y = BoxFinish.Y;

	//	UE_LOG(LogTemp, Warning, TEXT("BoxDown %f %f  %f %f   "), BoxDown.X, BoxDown.Y, BoxRight.Y, BoxLeft.Y);

	const EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::None;
 
	//	const EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::None;
 

	Orientation = FRotator(0.0f, 0.0f, 0.f);
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	FVector BCenter1 = (BoxUp + BoxRight) / 2;
	FVector BCenter2 = (BoxDown + BoxLeft) / 2;
	BCenter1.Z = MouseZ;
	BCenter2.Z = MouseZ;

	BoxRadius.X = (FVector::Dist(BoxRight, BoxUp) / 2);
	BoxRadius.Y = 0.f;
	BoxRadius.Z = 50.f;
	bool Result = UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetWorld(),
		BCenter1,
		BCenter2,
		BoxRadius,
		Orientation,
		ObjectTypes,
		false,
		ActorsToIgnore,
		DrawDebugType,
		OutHits,
		true
	);

	if (Result == true)
	{
		if (OutHits.Num() > 0)
		{
			if (Charac.Num() > 0)
			{
				for (int32 s = 0; s < Charac.Num(); s++)
				{
					ABaseCharacter *  BaseCharacter_tmp = Cast<ABaseCharacter>(Charac[s]);
					if (BaseCharacter_tmp)
					{
						//	UE_LOG(LogTemp, Warning, TEXT("Charac.Num() %d "), Charac.Num());
						BaseCharacter_tmp->bBattleSelectedCursor = false;
					}
				}
			}
			Charac.Empty();
			HUDCharacter.Empty();
		}
		for (int32 i = 0; i < OutHits.Num(); i++)
		{
			FHitResult Hit = OutHits[i];
			ABaseCharacter *  BaseCharacter = Cast<ABaseCharacter>(Hit.GetActor());
			if (BaseCharacter)
			{

				ChangeHeroes = true;
				BaseCharacter->bBattleSelectedCursor = true;
				Charac.Add(BaseCharacter);
				HUDCharacter.Add(BaseCharacter);
			}
		}
	}
	int SLine = 6;
	FColor Color = FColor(34, 139, 34);

	// Draw a box that we have identified 
	DrawDebugLine(GetWorld(), BoxUp, BoxLeft, Color, false, 0, 0, SLine);
	DrawDebugLine(GetWorld(), BoxLeft, BoxDown, Color, false, 0, 0, SLine);
	DrawDebugLine(GetWorld(), BoxDown, BoxRight, Color, false, 0, 0, SLine);
	DrawDebugLine(GetWorld(), BoxRight, BoxUp, Color, false, 0, 0, SLine);

	if (!ChangeHeroes &&  Charac.Num() > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("AWindController::RightActionMouseIsland() --------------"));
		Charac.Empty();
		HUDCharacter.Empty();

		for (TActorIterator<ABaseCharacter> ActorHero(GetWorld()); ActorHero; ++ActorHero)
		{
			ABaseCharacter *Hero = *ActorHero;
			if (Hero && Hero->MouseEvent)
			{
				ChangeHeroes = true;
				Hero->bBattleSelectedCursor = true;
				Charac.Add(Hero);
				HUDCharacter.Add(Hero);
				UE_LOG(LogTemp, Warning, TEXT("AWindController::RightActionMouseIsland() ====1"));
			}
		}

	}

	if (!ChangeHeroes &&  Charac.Num() == 0)
	{

		for (TActorIterator<ABaseCharacter> ActorHero(GetWorld()); ActorHero; ++ActorHero)
		{
			ABaseCharacter *Hero = *ActorHero;
			if (Hero && Hero->MouseEvent)
			{
				ChangeHeroes = true;
				Hero->bBattleSelectedCursor = true;
				Charac.Add(Hero);
				HUDCharacter.Add(Hero);
				UE_LOG(LogTemp, Warning, TEXT("AWindController::RightActionMouseIsland() ====2"));
			}
		}

	}
}

void UWindComponent::Server_DefaultMouseClick() {

	if (Charac.Num() > 0) {

		UE_LOG(LogTemp, Warning, TEXT(" UAWindController::Server_DefaultMouseClick()"));

		for (int32 i = 0; i < Charac.Num(); i++)
		{
			if (Charac[i] && Charac[i]->Attributes->GetMyHero())
			{

				UE_LOG(LogTemp, Warning, TEXT(" Charac[i]->Attributes->GetMyHero() true"));
				BaseCharacterMyHero.Add(Charac[i]);
				MyHeroBranch = true;
				if (Charac[i]->tpm_IsLand)
				{
					UE_LOG(LogTemp, Warning, TEXT(" if (Charac[i]->tpm_IsLand)"));
					__MouseClickMoveChar(Charac[i]);
				}
			}
			else {

				UE_LOG(LogTemp, Warning, TEXT(" Charac[i]->Attributes->GetMyHero() false"));
			}
		}
	}
}


void UWindComponent::SelectedCharacter(APlayerController* PlayerController) {
	// Selecter mouse character
	MouseSelectedHUD = false;
	// set flag to keep updating destination until released
	 
	FHitResult HitResult;
	PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

	BoxStart = HitResult.Location;
	BoxUp.Z = BoxStart.Z + MouseZ;
	BoxRight.Z = BoxStart.Z + MouseZ;
	BoxDown.Z = BoxStart.Z + MouseZ;
	BoxLeft.Z = BoxStart.Z + MouseZ;

	BoxUp.X = BoxStart.X;
	BoxUp.Y = BoxStart.Y;
	BoxLeft.X = BoxStart.X;
	BoxRight.Y = BoxStart.Y;

	// remove selection from previously selected characters
	if (BaseCharacterMyHero.Num() > 0) {

		for (int32 i = 0; i < BaseCharacterMyHero.Num(); i++)
		{
			if (BaseCharacterMyHero[i]->Attributes->GetMyHero())
			{
				// mark that the hero no longer has the selection
				BaseCharacterMyHero[i]->bBattleSelectedCursor = false;
			}
		}
		BaseCharacterMyHero.Empty();
	}


	MyHeroBranch = false;
	UE_LOG(LogTemp, Warning, TEXT("AWindController::SelectedCharacter 4"));

}


/**
* Moving to the island
*/
void UWindComponent::__MouseClickMoveChar(ABaseCharacter* ObjCharacter)
{

	UE_LOG(LogTemp, Warning, TEXT(" AWindController::__MouseClickMoveChar(ABaseCharacter* ObjCharacter)"));
	if (ObjCharacter->IsLand)
	{
		if (ObjCharacter->tpm_IsLand != ObjCharacter->IsLand) {
			ObjCharacter->IsLand = ObjCharacter->tpm_IsLand;
			//	ObjCharacter->IsLand->StartMove();
			ObjCharacter->bCanBuildIsland = true;
		}
		else
		{
			ObjCharacter->bCanBuildIsland = true;
		}
	}
	else
	{
		ObjCharacter->IsLand = ObjCharacter->tpm_IsLand;
		ObjCharacter->bCanBuildIsland = true;
	}
}

void UWindComponent::SetNewLocationBuilder() {

	if (Charac.Num() == 1) {
		if (Charac[0]->tpm_IsLand)
		{
			if (Charac[0]->tpm_IsLand->StatusBuildung == 0)
			{
				if (SpawnNewBilderLocation) {
					SpawnNewBilderLocation = false;
					if (iMeshBuilder) {

						if (SingleLand) {
							if (Charac[0]->bIsAbordage) {

								// If the hero drags the island to the boarding, then it must be removed
								Charac[0]->RemovingIslandAbordage();
							}

							// Here is a new action with a new island.
							UE_LOG(LogTemp, Warning, TEXT("AWindController::SetNewLocationBuilder "));
							Charac[0]->tpm_IsLand = SingleLand;
							SingleLand->Builder = iMeshBuilder;

							iMeshBuilder->StartSpawn();
							iMeshBuilder->BuildFraction = Charac[0]->HeroFraction;
							// create builder  
							Charac[0]->FollowTheIslandFunction();
							//  Making HUD change available
							NotChangeHud = true;
							UE_LOG(LogTemp, Warning, TEXT("AWindController::SetNewLocationBuilder 2"));
						}
					}
				}
				else {
					//	UE_LOG(LogTemp, Warning, TEXT("Error SpawnNewBilderLocation = false"));
				}
				BuilderBarrakActive = false;
			}
			else {
				//	UE_LOG(LogTemp, Warning, TEXT("not Builder, fails"));
			}
		}
	}
	else {
		//	UE_LOG(LogTemp, Warning, TEXT("Island, fails"));
	}
}



void UWindComponent::SetNewLocationBuilderAbordage() {

	if (Charac.Num() == 1) { 
		if (Charac[0]->Attributes->GetMyHero())
		{ 

			if (Charac[0]->IsLand)
			{ 


				if (!Charac[0]->IsLand->Abordage) 




					if (!Charac[0]->IsLand->AbordageIsland) {
						//	UE_LOG(LogTemp, Warning, TEXT("Charac[0]->IsLand->AbordageIsland nothing is built on the island its boarding"));
					}
				if (Charac[0]->bIsAbordage) {
					// If the hero drags the island to the boarding, then it must be removed
					//	UE_LOG(LogTemp, Warning, TEXT("AWindController::SetNewLocationBilderAbordage 5.1"));
					Charac[0]->RemovingIslandAbordage();
				}
				//	UE_LOG(LogTemp, Warning, TEXT("7 This a testing statement. %s"), *Charac[0]->IsLand->GetName());
				if (Charac[0]->IsLand->StatusBuildung == 0)
				{


					//	UE_LOG(LogTemp, Warning, TEXT("8 This a testing statement. %s"), *Charac[0]->IsLand->GetName());
					//	UE_LOG(LogTemp, Warning, TEXT("AWindController::SetNewLocationBilderAbordage 5"));
					// Making HUD change available
					//	Charac[0]->IsLand->StatusBuildung = 1;
					NotChangeHud = true;
					Charac[0]->SelectEraseToBoarding = true;
					// Unlock button
					Charac[0]->HUDabordage = true;
					// Remove the island from the cursor
					// attach to the island.
					SetNewLocationBuilder();
					//	UE_LOG(LogTemp, Warning, TEXT("9 This a testing statement. %s"), *Charac[0]->IsLand->GetName());
				}
				else {
					//	UE_LOG(LogTemp, Warning, TEXT("There is no island or there is boarding or the island cannot be boarding"));
				}
			}
		}
	}
}

void UWindComponent::PatrolGO(APlayerController* PlayerController) {
	// 	SpawnCursorPoint();

	bool MouseClick = false;

	TArCharacterStructure.Empty();
	//UE_LOG(LogTemp, Warning, TEXT("patrule"));
	FHitResult TMP;
	PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, TMP);

	 TMP_location = TMP.Location;
	if (BaseCharacterMyHero.Num() > 0) {
		for (int32 i = 0; i < BaseCharacterMyHero.Num(); i++)
		{
			if (BaseCharacterMyHero[i]->Attributes->GetMyHero())
			{
				BaseCharacterStructure.ActorCharacter = BaseCharacterMyHero[i];
				TArCharacterStructure.Add(BaseCharacterStructure);
				MouseClick = true;
				//	UE_LOG(LogTemp, Warning, TEXT(" 1 UNITS PATROL %d"), i);
			}
		}

		CobeShip(TMP_location, TArCharacterStructure);
		if (TArCharacterStructure.Num() > 0)
		{
			for (int32 i = 0; i < TArCharacterStructure.Num(); i++)
			{

				if (TArCharacterStructure[i].ActorCharacter->Attributes->GetMyHero())
				{

					FVector L = TArCharacterStructure[i].location;

					float dist = FVector::Dist(L, TArCharacterStructure[i].ActorCharacter->GetActorLocation());

					if (dist > 300)
					{
						isPatrol = true;
						BaseCharacterTimer = TArCharacterStructure[i].ActorCharacter;
						BaseCharacterTimer->BreakCommand();
						BaseCharacterTimer->Server_PatrolToTepeat(L);
					}
					else
					{
						//	UE_LOG(LogTemp, Warning, TEXT(" UNITS PATROL %d %f %f"), i, L.X, dist);

					}
				}
			}
		}
	}

	if (MouseClick)
	{
	//	SpawnCursorPoint();
	}
}


bool  UWindComponent::BuildBreak() {

	if (iMeshBuilder) {
		iMeshBuilder->Destroy();
		SpawnNewBilderLocation = false;
		//	UE_LOG(LogTemp, Warning, TEXT("SpawnNewBilderLocation = false;"));

		if (Charac.Num() == 1)
		{
			Charac[0]->SelectEraseToBoarding = false;
		}
		return true;
	}
	return false;

}


/**
* Client search Garbage
* Search for island installations building
*/
void UWindComponent::SetActorLocationHeroes(APlayerController* PlayerController)
{
	bool isHeroesBlock = false;
	if (SpawnNewHeroesLocation) {
		 SpawnNewBilderLocation = false;
		FHitResult SpawnHit;
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, SpawnHit);
		// get currentassss location mouse
		if (Charac.Num() == 1) {
			FVector  Loc = SpawnHit.Location;
			//	traceIsland(Loc);
			Loc.Z = 0.f;
			if (iBaseCharacterSpawn) {
				Charac[0]->bCanBuildIsland = false;
				//	bWindYouCanBuild = false; 

				traceGarbage(Loc);
				//	iBaseCharacterSpawn -> ChangeColorGood();
				isHeroesBlock = true;
				bWindYouCanBuild = true;
				Charac[0]->bCanBuildIsland = true;
				//	EventUnit = 0; //  
			}
			else
			{
				///	UE_LOG(LogTemp, Warning, TEXT(" iBaseCharacterSpawn   103"));
				//	iBaseCharacterSpawn->ChangeColorWarning();
			}
			if (!isHeroesBlock) {
				iBaseCharacterSpawn->ChangeColorDefault();
			}
			iBaseCharacterSpawn->SetActorLocation(Loc);
			iBaseCharacterSpawn->SetActorRotation(FRotator(0.f, 0.f, 0.f));
			//	}
		}
	}
}


bool UWindComponent::traceGarbage(FVector Start) { 
	return true;
	if (SpawnNewHeroesLocation)
	{
	//	EventUnit = 8;
	//	SpawnDrone = true;

		TArray<AActor*> AttackActorsToIgnore;
		TArray< TEnumAsByte<EObjectTypeQuery> > ObjectTypes;
		FHitResult HitData;
		TArray<FHitResult>  OutHits;
		//	AttackActorsToIgnore.Add(GetOwner());
		Start.Z = Start.Z - 10;
		Start.Y = Start.Y - 2;
		Start.X = Start.X - 2;
		const FVector End = FVector(Start.X, Start.Y, Start.Z - 900);

		const EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::None;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

		bool Result = UKismetSystemLibrary::LineTraceMultiForObjects(
			GetWorld(),
			Start,	//start
			End, //end 
			ObjectTypes,
			true,
			AttackActorsToIgnore,
			EDrawDebugTrace::ForOneFrame,
			OutHits,
			true);

		//	OutHits.Add(HitData);

		if (Result)
		{
			if (OutHits.Num() > 0)
			{
				for (int32 i = 0; i < OutHits.Num(); i++)
				{
				//	FHitResult Hit = OutHits[i];
				//	AGarbageGround * Garbage = Cast<AGarbageGround>(Hit.GetActor());
				//	if (Garbage)
				//	{
				//		//	UE_LOG(LogTemp, Warning, TEXT("  %i"), i);
				//		youCanBuildDrone = true;
				//		iBaseCharacterSpawn->ChangeColorReserved();
//
				//		return true;
				//	}
				//	else { 
				//		iBaseCharacterSpawn->ChangeColorWarning();
				//		youCanBuildDrone = false;
				//	}
				}
			}
		}
		if (iBaseCharacterSpawn)
		{
			iBaseCharacterSpawn->ChangeColorWarning();
		} 
	//	youCanBuildDrone = false;
	}
	return false;

}


void UWindComponent::ChoiceBuildingPoint(APlayerController* PlayerController) {
	FVector SpawnLocation = FVector(FMath::FRand() *158.f, FMath::FRand() * 158.f, 0.f);
	FRotator  SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = PlayerController;
	//Instigator = PlayerController->GetPawn();
	//Instigator = cast<APawn>(NewOwner);
//	SpawnParams.Instigator = Instigator;

	switch (iBuildStrange)
	{
	case 1:
	{
		//	iMeshBuilder = GetWorld()->SpawnActor<AVerf>(SpawnLocation, SpawnRotation, SpawnParams);
		break;
	}
	case 2:
	{
		//	iMeshBuilder = GetWorld()->SpawnActor<AMainBuilding>(SpawnLocation, SpawnRotation, SpawnParams);
		break;
	}
	case 3:
	{
		//	UE_LOG(LogTemp, Warning, TEXT("void AWindController::ChoiceBuildingPoint() iBaseCharacterSpawn = true;"));
		//	iBaseCharacterSpawn = GetWorld()->SpawnActor<ARsourceDroneH>(SpawnLocation, SpawnRotation, SpawnParams);
		//	iBaseCharacterSpawn->ChangeColorReserved();
		break;
	}
	default:
	{
		break;
	}
	}

	 
	//	}
}


void UWindComponent::LogicAI(APlayerController* PlayerController)
{
	// create bilder
	if (BuilderBarrakActive) {
		//	CreateBilder = true; 
		ChoiceBuildingPoint( PlayerController);
		//	UE_LOG(LogTemp, Warning, TEXT("get builder +++++++++++"));
	}
	else {
		if (SpawnNewBilderLocation && !BuilderBarrakActive) {

			//	UE_LOG(LogTemp, Warning, TEXT("SpawnNewBilderLocation == true"));
			CenselHeroIsBuilding();
			SetNewLocationBuilder();
			//	UE_LOG(LogTemp, Warning, TEXT("go new loc"));
		}
		else
		{
			//	UE_LOG(LogTemp, Warning, TEXT("SpawnNewBilderLocation == false"));
		}
	}
}

 
void UWindComponent::CenselHeroIsBuilding()
{
	if (Charac.Num() > 0) {
		for (int32 Index = 0; Index != Charac.Num(); ++Index)
		{
			if (Charac[Index]) {
			//	Charac[Index]->CancelAllCommands();
			//	Charac[Index]->FailsHeroIsBuilding();
			//	if (Charac[Index]->GoIslandPoint) {

			//	}
			}
		}
	}
}
 