#include "WindController.h"


AWindController::AWindController()
{

}

void AWindController::BeginPlay()
{
	Super::BeginPlay();
}
void AWindController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
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

	UE_LOG(LogTemp, Warning, TEXT("LeftMouseStart 1"));
}
void AWindController::LeftMouseStop() {
	UE_LOG(LogTemp, Warning, TEXT("LeftMouseStop 2 "));

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
void AWindController::NewLocation(){}
void AWindController::CenselHeroIsBuilding(){}
void AWindController::PatrolGO(){}
void AWindController::Server_DefaultMouseClick(){}
void AWindController::SelectedBuilder(){}
void AWindController::ClearVar() {}
void AWindController::RightActionMouseIsland(){}
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

bool AWindController::BuildStractionName(int32 iBuildName){ return true; }
bool AWindController::BuildBreak() { return true; }

void AWindController::SelectedCharacter() {}
void AWindController::SetCommandSpawnDrone(){}


void AWindController::IslandFollowsTheHero() {}

void AWindController::CursorOverOut() {}

void   AWindController::CobeShip(){}

void AWindController::SetNewLocationBuilderAbordage() {}

FVector AWindController::GetPointCursor(){
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	FVector vHit = HitResult.Location;
	return  vHit;
}

void AWindController::SetNewLocationBuilder(){}
void AWindController::SetActorLocationBilder(){}

bool AWindController::HeroesBreak(){ return true; }

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


bool AWindController::SetNewBilder() {return true;}

void AWindController::GetAllMyHero(){}

void AWindController::LogicAI(){}
