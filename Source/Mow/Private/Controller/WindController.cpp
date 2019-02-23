#include "WindController.h"


AWindController::AWindController()
{
	//whether the right mouse button is clamped
	bPressRightMouseKey = false;
}

void AWindController::BeginPlay()
{
	Super::BeginPlay();
}
void AWindController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	GetBoxMouseCursor();
	SetActorLocationBilder();
	SetActorLocationHeroes();
	SetActorLocationAbordageIsland();
	CursorOverOut();


}

void AWindController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();


	InputComponent->BindAction("LeftMouse", IE_Pressed, this, &AWindController::LeftMouseStart);
	InputComponent->BindAction("LeftMouse", IE_Released, this, &AWindController::LeftMouseStop);
	InputComponent->BindAction("RightMouse", IE_Pressed, this, &AWindController::RightActionMouse);
	InputComponent->BindAction("RightMouse", IE_Released, this, &AWindController::RightActionStop);

	InputComponent->BindAction("BattleDetect", IE_Pressed, this, &AWindController::BattleDetectStart);
	InputComponent->BindAction("BattleDetect", IE_Released, this, &AWindController::BattleDetectStop);


}

/**
* Client search Garbage 
* Search for island installations building
*/
void AWindController::SetActorLocationHeroes()
{
	bool isHeroesBlock = false;
	if (SpawnNewHeroesLocation) {
		SpawnNewBilderLocation = false;
		FHitResult SpawnHit;
		GetHitResultUnderCursor(ECC_Visibility, false, SpawnHit);
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

void AWindController::LeftMouseStart() {

	UE_LOG(LogTemp, Warning, TEXT("LeftMouseStart 1"));
	if (Charac.Num() == 1) {
		if (Charac[0]->tpm_IsLand)
		{
			UE_LOG(LogTemp, Warning, TEXT("AWindController::LeftMouseStart() Charac[0]->tpm_IsLand 111"));
		}
	}


	UE_LOG(LogTemp, Warning, TEXT("AWindController::LeftMouseStart ==== start ======EventUnit  %d"), iStateController);
	if (bBattleVector)
	{
		bBattleCursor = true;
		// Prohibited any action
		return;
	}

	BuildViewportCanvas = false;

	//Do not turn off HUD
	if (NotChangeHud) {
		GetAllMyHero();

		isPatrol = false;
		// Selecter mouse character 
		switch (iStateController) {
		case 0:
		{
			if (!bWindYouCanBuild) {
				UE_LOG(LogTemp, Warning, TEXT("AWindController::LeftMouseStart() log case 1 "));
				// selection of heroes on the map
				if (Charac.Num() == 1) {
					if (Charac[0]->MyHero == true)
					{
						if (Charac[0]->tpm_IsLand)
						{
							UE_LOG(LogTemp, Warning, TEXT("Charac[0]->tpm_IsLand"));
						}
						if (Charac[0]->IsLand)
						{
							UE_LOG(LogTemp, Warning, TEXT("Charac[0]->IsLand 1"));
						}
					}
				}
				SelectedCharacter();
				// selection of buildings on the map
				SelectedBuilder();
			}
		}
		break;
		case 1:
		{
			// move actor/ group 
		}
		break;
		case 2:
		{

			//	UE_LOG(LogTemp, Warning, TEXT("UNITS PATROL"));
			PatrolGO();
			// break
			iStateController = 0;
		}
		break;
		case 3:
		{
			// fight  actor / group 
		}
		break;
		case 4:
		{
			if (bWindYouCanBuild) {
				//	UE_LOG(LogTemp, Warning, TEXT("bWindYouCanBuild = true"));
				// construct buildings 


				SetNewLocationBuilderAbordage();
				SetNewLocationBuilder();
				iStateController = 0;
			}
			else {
				//	UE_LOG(LogTemp, Warning, TEXT("AWindController::LeftMouseStart() = false"));
				//		SetNewLocationBuilderAbordage();
			}
		}
		break;
		case 5:
		{
			iStateController = 0;
			// fight  actor / group 
			//UE_LOG(LogTemp, Warning, TEXT("default mouse "));

			// try to choose the characters
			Server_DefaultMouseClick();

			// selection of heroes on the map
			SelectedCharacter();
			// selection of buildings on the map
			SelectedBuilder();
		}
		break;
		case 8:
		{

			//UE_LOG(LogTemp, Warning, TEXT("build drone"));
			SetCommandSpawnDrone();
		}
		break;
		default:
			//	UE_LOG(LogTemp, Warning, TEXT("default mouse "));
			break;
		}

		BaseCharacterMyHero.Empty();
		MyHeroBranch = false;

	}
	else {
		// click on the button
		LogicAI();
		//	UE_LOG(LogTemp, Warning, TEXT(" AWindController::LeftMouseStart NotChangeHud false"));
	}
	//Boarding

	UE_LOG(LogTemp, Warning, TEXT("AWindController::LeftMouseStart ==== end  ======EventUnit  %d"), iStateController);
}
void AWindController::LeftMouseStop() {
	UE_LOG(LogTemp, Warning, TEXT("LeftMouseStop 2 "));
	bBattleCursor = false;
	//  Do not turn off HUD
	if (NotChangeHud) {
		bPressRightMouseKey = false;
		MouseSelectedHUD = true;
	}

}
void AWindController::RightActionMouse() {
	UE_LOG(LogTemp, Warning, TEXT("RightActionMouse 3"));
	if (HeroesBreak())return;

	switch (iStateController) {
	case 0:
	{
		RightActionMouseIsland();
		//	UE_LOG(LogTemp, Warning, TEXT("AWindController::RightActionMouse() log 1"));
		if (!bWindYouCanBuild) { // The building is not attached
								 //		UE_LOG(LogTemp, Warning, TEXT("AWindController::RightActionMouse() log 2"));
			Server_DefaultMouseClick();
		}

		break;
	}
	case 1:
	{
		SpawnCursorPoint();
	}
	break;
	case 4:
	{
		SpawnCursorPoint();
		BuildBreak();
		return;
	}
	break;
	case 5:
	{

		SelectedBuilder();
		return;
	}
	break;
	case 6:
	{
		SpawnCursorPoint();
		//	HeroesBreak();
		return;
	}
	break;
	default:

		break;
	}



	if (NotChangeHud) {
		FHitResult MouseLocation;
		GetHitResultUnderCursor(ECC_Visibility, false, MouseLocation);
		TMP_location = MouseLocation.Location;
		SortCharacter();
		if (TArCharacterStructure.Num() > 0) {
			for (int32 Index = 0; Index != TArCharacterStructure.Num(); ++Index)
			{
				if (TArCharacterStructure[Index].ActorCharacter->MyHero == true)
				{
					BaseCharacterTimer = TArCharacterStructure[Index].ActorCharacter;
					BaseCharacterTimer->BreakCommand();
					BaseCharacterTimer->SetNewLocation(TArCharacterStructure[Index].location);

				}
			}
		}
		ArrayNeighbors.Empty();
		CenselHeroIsBuilding();
	}
	else {
		NotChangeHud = true;
	}

	//	iBuildStrange = 0;
	if (!SpawnNewBilderLocation) {
		SpawnCursorPoint();
	}
	IslandFollowsTheHero();
}



/*
* We touch the heroes to sort from the far point to the near
*  Itteration heroes for check point
*/
void AWindController::SortCharacter()
{
	//UE_LOG(LogTemp, Warning, TEXT("get point Start"));
	TArCharacterStructure.Empty();
	for (int32 Index = 0; Index != Charac.Num(); ++Index)
	{
		if (Charac[Index]) {
			if (Charac[Index]->MyHero == true)
			{
				//	const FVector TMP_locActor = Charac[Index]->GetActorLocation();
				//	BaseCharacterStructure.Distance = FVector::Dist(TMP_location, TMP_locActor);
				BaseCharacterStructure.ActorCharacter = Charac[Index];
				TArCharacterStructure.Add(BaseCharacterStructure);
			}
		}
	}
	CobeShip();
}



void AWindController::RightActionStop() {
	UE_LOG(LogTemp, Warning, TEXT("RightActionStop 4"));
}
void AWindController::BattleDetectStart() {}
void AWindController::BattleDetectStop() {}
void AWindController::ChoiceBuildingPoint() {}




void AWindController::BehindTheIslandBoarded() {
	if (Charac.Num() > 0) {
		for (int32 Index = 0; Index != Charac.Num(); ++Index)
		{
			GetIslandAbordage = true;
		}
	}
}
void AWindController::NewLocation() {}
void AWindController::CenselHeroIsBuilding() {}
void AWindController::PatrolGO() {
	// 	SpawnCursorPoint();

	bool MouseClick = false;

	TArCharacterStructure.Empty();
	//UE_LOG(LogTemp, Warning, TEXT("patrule"));
	FHitResult TMP;
	GetHitResultUnderCursor(ECC_Visibility, false, TMP);
	TMP_location = TMP.Location;
	if (BaseCharacterMyHero.Num() > 0) {
		for (int32 i = 0; i < BaseCharacterMyHero.Num(); i++)
		{
			if (BaseCharacterMyHero[i]->MyHero == true)
			{
				BaseCharacterStructure.ActorCharacter = BaseCharacterMyHero[i];
				TArCharacterStructure.Add(BaseCharacterStructure);
				MouseClick = true;
				//	UE_LOG(LogTemp, Warning, TEXT(" 1 UNITS PATROL %d"), i);
			}
		}

		CobeShip();
		if (TArCharacterStructure.Num() > 0)
		{
			for (int32 i = 0; i < TArCharacterStructure.Num(); i++)
			{

				if (TArCharacterStructure[i].ActorCharacter->MyHero == true)
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
		SpawnCursorPoint();
	}
}
void AWindController::Server_DefaultMouseClick() {
	if (Charac.Num() > 0) {
		for (int32 i = 0; i < Charac.Num(); i++)
		{
			if (Charac[i] && Charac[i]->MyHero)
			{

				BaseCharacterMyHero.Add(Charac[i]);
				MyHeroBranch = true;
				if (Charac[i]->tpm_IsLand)
				{
					__MouseClickMoveChar(Charac[i]);
				}
			}
		}
	}
}
void AWindController::SelectedBuilder() {

	UE_LOG(LogTemp, Warning, TEXT("AWindController::SelectedBuilder()  0 "));
	TArray<AActor*> build;
	for (TActorIterator<ABaseBuilding> build(GetWorld()); build; ++build)
	{
		ABaseBuilding *PlayerBuild = *build;
		if (PlayerBuild && PlayerBuild->MyBuild && PlayerBuild->MouseBuildViewPort && PlayerBuild->BuildViewPort)
		{
			// clear all var
			ClearVar();
			BuildController = PlayerBuild;
			BuildViewportCanvas = true;
			iStateController = 5;
			UE_LOG(LogTemp, Warning, TEXT("AWindController::SelectedBuilder() %s"), *BuildController->BuilderName);
		}
	}
}
void AWindController::ClearVar() {}
void AWindController::RightActionMouseIsland() {}
void AWindController::GetBoxMouseCursor() {
	// work uilder
	if (!BuilderBarrakActive)
	{
		//Do not turn off HUD
		if (NotChangeHud) {
			// selected actor
			if (bPressRightMouseKey)
			{

				FHitResult HitResult;
				GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
				BoxFinish = HitResult.Location;
				BoxDown.X = BoxFinish.X;
				BoxDown.Y = BoxFinish.Y;
				BoxRight.X = BoxFinish.X;
				BoxLeft.Y = BoxFinish.Y;

				const EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::None;
				if (Production)
				{
					//	const EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::None;
				}

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
		}
	}

}
void AWindController::traceIsland(FVector Start) {}
bool AWindController::traceGarbage(FVector Start) { return true; }

bool AWindController::BuildStractionName(int32 iBuildName) { return true; }
bool AWindController::BuildBreak() { return true; }

void AWindController::SelectedCharacter() {
	// Selecter mouse character
	MouseSelectedHUD = false;
	// set flag to keep updating destination until released
	bPressRightMouseKey = true;
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

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
			if (BaseCharacterMyHero[i]->MyHero == true)
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
void AWindController::SetCommandSpawnDrone() {
}


void AWindController::IslandFollowsTheHero() {}

void AWindController::CursorOverOut() {

	for (TActorIterator<ABaseCharacter> ActorHero(GetWorld()); ActorHero; ++ActorHero)
	{
		ABaseCharacter * Hero = *ActorHero;
		if (Hero && Hero->MouseEvent)
		{
			//		UE_LOG(LogTemp, Warning, TEXT("AWindController::CursorOverOut() "));
		}
	}
}

void   AWindController::CobeShip() {}

void AWindController::SetNewLocationBuilderAbordage() {}

FVector AWindController::GetPointCursor() {
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	FVector vHit = HitResult.Location;
	return  vHit;
}

void AWindController::SetNewLocationBuilder() {
	 
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
								UE_LOG(LogTemp, Warning, TEXT(" "));
								UE_LOG(LogTemp, Warning, TEXT("======"));
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
void AWindController::SetActorLocationBilder() {}

bool AWindController::HeroesBreak() { return true; }

void AWindController::SpawnCursorPoint()
{
	FHitResult TMP;
	GetHitResultUnderCursor(ECC_Visibility, false, TMP);
	TMP_location = TMP.Location;
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	FRotator  SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
	//ACursorPoint*  CursorPoint = GetWorld()->SpawnActor<ACursorPoint>(TMP_location, SpawnRotation, SpawnParams);
	//UE_LOG(LogTemp, Warning, TEXT("SpawnCursorPoint"));
}


bool AWindController::SetNewBilder() { return true; }

void AWindController::GetAllMyHero() {
	if (Charac.Num() > 0) {
		for (int32 i = 0; i < Charac.Num(); i++)
		{
			if (Charac[i] && Charac[i]->MyHero)
			{
				BaseCharacterMyHero.Add(Charac[i]);
				MyHeroBranch = true;
			}
		}
	}
}

void AWindController::LogicAI() {}



/**
* Moving to the island
*/
void AWindController::__MouseClickMoveChar(ABaseCharacter* ObjCharacter)
{

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



/**
*  
* Search Islands for boarding
*/
void AWindController::SetActorLocationAbordageIsland() {
	if (GetIslandAbordage && Charac.Num() == 1) {
		GetIslandAbordage = false;
		//  break search island
		UE_LOG(LogTemp, Warning, TEXT("AWindController::SetActorLocationAbordageIsland() Search island for abordage"));
	}
}
