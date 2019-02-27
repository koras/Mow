#include "WindController.h"


AWindController::AWindController()
{
	//whether the right mouse button is clamped
	bPressRightMouseKey = false;

	wComponent = CreateDefaultSubobject<UWindComponent>(TEXT("Attribute"));

	 
	 bBattleVector = false;

	// You can build a building or not, when choosing.
	 wComponent->bWindYouCanBuild = false;
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
	wComponent->SetActorLocationHeroes(this);
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
 

void AWindController::LeftMouseStart() {

	UE_LOG(LogTemp, Warning, TEXT("LeftMouseStart"));

	UE_LOG(LogTemp, Warning, TEXT("LeftMouseStart 1"));
	if (wComponent->Charac.Num() == 1) {
		if (wComponent->Charac[0]->tpm_IsLand)
		{
			UE_LOG(LogTemp, Warning, TEXT("AWindController::LeftMouseStart() Charac[0]->tpm_IsLand 111"));
		}
	}



	if (bBattleVector)
	{
		UE_LOG(LogTemp, Warning, TEXT("bBattleVector true") );
		bBattleCursor = true;
		// Prohibited any action
		return;
	}
	else {

			UE_LOG(LogTemp, Warning, TEXT("bBattleVector false")); 
		}

	BuildViewportCanvas = false;
	 
	//Do not turn off HUD
	if (wComponent->NotChangeHud) {
		GetAllMyHero(); 

		wComponent->isPatrol = false;
		// Selecter mouse character 
		switch (iStateController) {
		case 0:
		{
			UE_LOG(LogTemp, Warning, TEXT("iStateController %f"), iStateController);

			 
			if (!wComponent->bWindYouCanBuild) {
				UE_LOG(LogTemp, Warning, TEXT("iStateController--- %f"), iStateController);

				UE_LOG(LogTemp, Warning, TEXT("AWindController::LeftMouseStart() log case 1 "));
				// selection of heroes on the map
				if (wComponent->Charac.Num() == 1) {
					if (wComponent->Charac[0]->Attributes->GetMyHero())
					{
						if (wComponent->Charac[0]->tpm_IsLand)
						{
							UE_LOG(LogTemp, Warning, TEXT("Charac[0]->tpm_IsLand"));
						}
						if (wComponent->Charac[0]->IsLand)
						{
							UE_LOG(LogTemp, Warning, TEXT("Charac[0]->IsLand 1"));
						}
					}
				}
				bPressRightMouseKey = true;
				wComponent->SelectedCharacter(this);
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
			wComponent->PatrolGO(this);
		//	if (MouseClick)
		//	{
				SpawnCursorPoint();
		//	}
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
			if (wComponent->bWindYouCanBuild) {
				wComponent->SetNewLocationBuilderAbordage();
				wComponent->SetNewLocationBuilder();
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
			wComponent->Server_DefaultMouseClick();

			// selection of heroes on the map
			bPressRightMouseKey = true;
			wComponent->SelectedCharacter(this);
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

		wComponent->BaseCharacterMyHero.Empty();
		wComponent->MyHeroBranch = false;

	}
	else {
		// click on the button
		LogicAI();

	}
	//Boarding

	UE_LOG(LogTemp, Warning, TEXT("AWindController::LeftMouseStart ==== end  ======EventUnit  %d"), iStateController);
}

void AWindController::LeftMouseStop() {
	UE_LOG(LogTemp, Warning, TEXT("LeftMouseStop 2 "));
	bBattleCursor = false;
	//  Do not turn off HUD
	if (wComponent->NotChangeHud) {
		bPressRightMouseKey = false;
		wComponent->MouseSelectedHUD = true;
	}

}
void AWindController::RightActionMouse() {
	UE_LOG(LogTemp, Warning, TEXT("RightActionMouse 3")); 
	UE_LOG(LogTemp, Warning, TEXT("AWindController::RightActionMouse() iStateController %d "), iStateController);

	if (HeroesBreak())return; 

	switch (iStateController) {
	case 0:
	{
		RightActionMouseIsland();
		//	UE_LOG(LogTemp, Warning, TEXT("AWindController::RightActionMouse() log 1"));
		if (!wComponent->bWindYouCanBuild) { // The building is not attached
			UE_LOG(LogTemp, Warning, TEXT("AWindController::RightActionMouse() log 2"));
			wComponent->Server_DefaultMouseClick();
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
		wComponent->BuildBreak();

		iStateController = 0;
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


	if (wComponent->NotChangeHud) {

		FHitResult MouseLocation;
		GetHitResultUnderCursor(ECC_Visibility, false, MouseLocation);
		wComponent->TMP_location = MouseLocation.Location;



		wComponent->SortCharacter();
		if (wComponent->TArCharacterStructure.Num() > 0) {
			for (int32 Index = 0; Index != wComponent->TArCharacterStructure.Num(); ++Index)
			{
				if (wComponent->TArCharacterStructure[Index].ActorCharacter->Attributes->GetMyHero())
				{
					wComponent->BaseCharacterTimer = wComponent->TArCharacterStructure[Index].ActorCharacter;
					wComponent->BaseCharacterTimer->BreakCommand();
					wComponent->BaseCharacterTimer->SetNewLocation(wComponent->TArCharacterStructure[Index].location);
				}
			}
		}
		ArrayNeighbors.Empty();
		CenselHeroIsBuilding();
	}
	else {
		wComponent->NotChangeHud = true;
	}

	//	iBuildStrange = 0;
	if (!wComponent->SpawnNewBilderLocation) {
		SpawnCursorPoint();
	}
	IslandFollowsTheHero();
}


 


void AWindController::RightActionStop() {
	UE_LOG(LogTemp, Warning, TEXT("RightActionStop 4"));
}
void AWindController::BattleDetectStart() {
	//	UE_LOG(LogTemp, Warning, TEXT("BattleDetectStart"));
	// bBattleVector;
	bBattleVector = true;

}

void AWindController::BattleDetectStop() {
	//	UE_LOG(LogTemp, Warning, TEXT("BattleDetectStop"));
	bBattleVector = false;
}
 




void AWindController::BehindTheIslandBoarded() {
	if (wComponent->Charac.Num() > 0) {
		for (int32 Index = 0; Index != wComponent->Charac.Num(); ++Index)
		{
			GetIslandAbordage = true;
		}
	}
}
void AWindController::NewLocation() {}
void AWindController::CenselHeroIsBuilding() {}

 
 


void AWindController::SelectedBuilder() {

	UE_LOG(LogTemp, Warning, TEXT("AWindController::SelectedBuilder()  0 ") );
	TArray<AActor*> build;
	for (TActorIterator<ABaseBuilding> build(GetWorld()); build; ++build)
	{
		ABaseBuilding *PlayerBuild = *build;
		if (PlayerBuild && PlayerBuild->MyBuild && PlayerBuild->MouseBuildViewPort && PlayerBuild->BuildViewPort)
		{
			// clear all var
			ClearVar();
			wComponent->BuildController = PlayerBuild;
			BuildViewportCanvas = true;
			iStateController = 5; 
		}
	}
}
void AWindController::ClearVar() {}
void AWindController::RightActionMouseIsland() {
	for (TActorIterator<ABaseLand> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ABaseLand *Island = *ActorItr;
		if (Island && Island->ChoosenIslandCursor)
		{
			UE_LOG(LogTemp, Warning, TEXT("AWindController::RightActionMouseIsland() "));
			Island->SetHero();
		}
	}

}
void AWindController::GetBoxMouseCursor() {
	// work uilder
	if (!wComponent->BuilderBarrakActive)
	{
		 
		//Do not turn off HUD
		if (wComponent->NotChangeHud) {
			// selected actor
			if (bPressRightMouseKey)
			{
				wComponent->GetBoxMouseCursor(this);
			}
		}
	}

}




void AWindController::traceIsland(FVector Start) {}
 

bool AWindController::BuildStractionName(int32 iBuildName) {
	if (wComponent->Charac.Num() == 1) {
		//UE_LOG(LogTemp, Warning, TEXT("Build %i"), iBuildName);
		wComponent->iBuildStrange = iBuildName;
		wComponent->ChoiceBuildingPoint(this);


		if (wComponent->iMeshBuilder) {
			iStateController = 4;
			wComponent->SpawnNewBilderLocation = true;

		}

		if (wComponent->iBaseCharacterSpawn)
		{
			iStateController = 6;
			wComponent->SpawnNewHeroesLocation = true;
			//	UE_LOG(LogTemp, Warning, TEXT("SpawnNewHeroesLocation = true;"));
		}

		return true;
	}
	return false;
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

 
 

FVector AWindController::GetPointCursor() {
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	FVector vHit = HitResult.Location;
	return  vHit;
}
 
void AWindController::SetActorLocationBilder() {}

bool AWindController::HeroesBreak() { 
	youCanBuildDrone = false;
	if (wComponent->SpawnNewHeroesLocation) {
		wComponent->SpawnNewHeroesLocation = false;
		wComponent->iBaseCharacterSpawn->Destroy();
		iStateController = 0;
		return true;
	}
	return false;

}

void AWindController::SpawnCursorPoint()
{
	FHitResult TMP;
	GetHitResultUnderCursor(ECC_Visibility, false, TMP);
	wComponent->TMP_location = TMP.Location;
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	FRotator  SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
	//ACursorPoint*  CursorPoint = GetWorld()->SpawnActor<ACursorPoint>(TMP_location, SpawnRotation, SpawnParams);
	//UE_LOG(LogTemp, Warning, TEXT("SpawnCursorPoint"));
}


bool AWindController::SetNewBilder() { return true; }

void AWindController::GetAllMyHero() {
	if (wComponent->Charac.Num() > 0) {
		for (int32 i = 0; i < wComponent->Charac.Num(); i++)
		{
			if (wComponent->Charac[i] && wComponent->Charac[i]->Attributes->GetMyHero())
			{
				wComponent->BaseCharacterMyHero.Add(wComponent->Charac[i]);
				wComponent->MyHeroBranch = true;
			}
		}
	}
}

void AWindController::LogicAI() {}


 


/**
*  
* Search Islands for boarding
*/
void AWindController::SetActorLocationAbordageIsland() {
	if (GetIslandAbordage && wComponent->Charac.Num() == 1) {
		GetIslandAbordage = false;
		//  break search island
		UE_LOG(LogTemp, Warning, TEXT("AWindController::SetActorLocationAbordageIsland() Search island for abordage"));
	}
}
