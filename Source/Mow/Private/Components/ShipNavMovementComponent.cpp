// Fill out your copyright notice in the Description page of Project Settings.

#include "ShipNavMovementComponent.h"



// Fill out your copyright notice in the Description page of Project Settings.

//#include "Last.h"

//#include "Public/WindController.h"
//#include "Public/BaseAIController.h"
//#include "Public/Heroes/RsourceDroneH.h"

/*
* https://habrahabr.ru/post/253711/ AIMoveTo
*/


UShipNavMovementComponent::UShipNavMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	LocationStartAndFinish = false;
	//	PointCurrentTarget = FVector(0, 0, 0);
	CheckPointOLD = FVector(1000, 5000, 5000);
	PointFinish = FVector(1000, 5000, 5000);
	CheckRange = 2500;
	rec_log = 0;
	Finish_recursion = false;
}


void UShipNavMovementComponent::BeginPlay()
{
	Super::BeginPlay();


	//TArray<AActor*> Island;
	///UGameplayStatics::GetAllActorsOfClass(GetWorld(), AIslandSingle::StaticClass(), Island);

	//for (int32 i = 0; i < Island.Num(); i++)
	//{
	//	ActorsToIgnore.Add(Island[i]);
//	}
	//FTimerHandle ChackTimerHandle;
	//GetWorld()->GetTimerManager().SetTimer(ChackTimerHandle, this, &UShipNavMovementComponent::CheckPoint, .33f, true);

	//	FTimerHandle ChackMoveActor;
	//	GetWorld()->GetTimerManager().SetTimer(ChackMoveActor, this, &ABaseAIController::MoveActor, .1f, true);
}

// Called every frame
/* 
void UShipNavMovementComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveToPositionCharacter();
	MoveActor();
	TickPatrol();
}*/

// Called every frame
void UShipNavMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	MoveToPositionCharacter();
	MoveActor();
	TickPatrol();
	// ...
}




void UShipNavMovementComponent::CheckPoint() {

	if (GoMove && ToActorCharacter) {
		FVector CurrentLocation = ToActorCharacter->GetActorLocation();
		FVector tmpForwardVector = ToActorCharacter->GetActorForwardVector();
		FVector tmpCurrentLocation = CurrentLocation;
		float LongDistance = FVector::Dist(CurrentLocation, PointFinish);
		float CurrentDistance = FVector::Dist(CurrentLocation, CheckPointOLD);
		float newRange = FVector::Dist(CurrentLocation, PointFinish);
		if (CurrentDistance <= iDistanceMin) {

			if (debug)
				UE_LOG(LogTemp, Warning, TEXT(" CurrentDistance < 25 we stand in places"));

			FVector start_point = CircumventionPoint(ToActorCharacter, PointCurrentTarget, 90.0f, 400.0f);
			getPointTarget(ToActorCharacter, start_point, PointFinish);
			NextPointLocation(CurrentLocation, PointFinish); 
			CheckPointOLD = CurrentLocation;
			OldRange = newRange;
			return;
		}

		// if the distance is greater
		if (LongDistance >= iDistanceMax)
		{ 
			if (TracePoint(ToActorCharacter, CurrentLocation, InFrontOfPoint(ToActorCharacter)))
			{  
				
				float ForceCrutch = 90.f;
				//	 PrimitivePawn->AddTorque(FVector(0, 0, Forcerutch), NAME_None, true);
				FVector PrimitiveForwardVector = PrimitivePawn->GetForwardVector();
				UE_LOG(LogTemp, Warning, TEXT("========== %f  %f  %f  "), PrimitiveForwardVector.X, PrimitiveForwardVector.Y, PrimitiveForwardVector.Z);
				float InRangeA = -200.f;
				float InRangeB = -10000.f;


				float OutRangeA = -13000.f;
				float OutRangeB = -150000.f;
				float RangeClamped = UKismetMathLibrary::MapRangeClamped(LenghtTarget, InRangeA, InRangeB, OutRangeA, OutRangeB);
				//FVector ForceVector = PrimitiveForwardVector * OutRangeB;
				FVector ForceVector = FVector(PrimitiveForwardVector.X * OutRangeB, PrimitiveForwardVector.Y * OutRangeB, 0);
				UE_LOG(LogTemp, Warning, TEXT("========== %f  %f  "), ForceVector.X, ForceVector.Y);
				// add strength
				//	PrimitivePawn->AddForce(ForceVector); 
				FRotator rt = ToActorCharacter->GetActorRotation();

				ToActorCharacter->SetActorRotation(FRotator(rt.Pitch + 180, rt.Yaw + 180, 0));
				const float  grad = 60.0f;
				//	FVector start_point1 = CircumventionPoint(ToActorCharacter, PointCurrentTarget, grad, 350.0f); 
				bool getPoint = false;

				PointCurrentCameraT = (ToActorCharacter->GetActorForwardVector()*1000.f) + ToActorCharacter->GetActorLocation();


				FHitResult  OutHit = TracePoint_recurs(ToActorCharacter, ToActorCharacter->GetActorLocation(), PointFinish);

				// calculate the angle of rotation
				tmpCurrentLocation = GetPoinAngel(OutHit.Location, ToActorCharacter->GetActorLocation(), 1);

				UE_LOG(LogTemp, Warning, TEXT("======== start_point1 %f %f  "), OutHit.Location.X, OutHit.Location.Y);
				UE_LOG(LogTemp, Warning, TEXT("======== start_point2 %f %f  "), tmpCurrentLocation.X, tmpCurrentLocation.Y);


				DrawDebugSphere(GetWorld(), tmpCurrentLocation, 200, 16, FColor(255, 255, 0), false, 1, 0);

				getPointTarget(ToActorCharacter, tmpCurrentLocation, PointFinish); // paving a new path
				NextPointLocation(CurrentLocation, PointFinish);

				OldRange = newRange;
			}
			else {
				//there are no obstacles

				if (debug)
					UE_LOG(LogTemp, Warning, TEXT("stop"));
				//	UE_LOG(LogTemp, Warning, TEXT("1stop  %f %f %f %f"), newRange, OldRange, CurrentDistance, LongDistance);

				if (newRange > OldRange + iDistanceMin)
				{

					if (debug)
						UE_LOG(LogTemp, Warning, TEXT("reversed, fael 6"));
					//	getPointTarget(ToActorCharacter, start_point1, PointFinish); // paving a new path
					NextPointLocation(CurrentLocation, PointFinish);

				}
			}
			OldRange = newRange;
			//	UE_LOG(LogTemp, Warning, TEXT("CurrentDistance %f"), CurrentDistance);
		}

		CheckPointOLD = CurrentLocation;
	}
}
//https://otvet.mail.ru/question/46536998
FVector UShipNavMovementComponent::rotateFVector(FVector point, float angle) {
	FVector  rotated_point;

	rotated_point.X = point.X * FMath::Cos(angle) - point.Y * FMath::Sin(angle);
	rotated_point.Y = point.X * FMath::Sin(angle) + point.Y * FMath::Cos(angle);
	return rotated_point;
}



// http://flashgamedev.ru/viewtopic.php?f=6&t=3948

FVector UShipNavMovementComponent::GetPoinAngel(FVector Center, FVector Ship, float alpha) {
	if (debug)
		UE_LOG(LogTemp, Warning, TEXT("ABaseAIController::GetPoinAngel "));
	FVector result, direction;

	float rx = Ship.X - Center.X;
	float ry = Ship.Y - Center.Y;
	float c = FMath::Cos(alpha);
	float s = FMath::Sin(alpha);

	result.X = Center.X + rx * c - ry * s;
	result.Y = Center.Y + rx * s + ry * c;
	result.Z = 0;
	direction = result;
	//	direction = (result-P1)* 200 + P1 ;
	direction.Z = 0;
	return direction;
}





void  UShipNavMovementComponent::MoveGo()
{
	GoMove = false;
	FVector start_point1 = CircumventionPoint(ToActorCharacter, PointCurrentTarget, 60, 350.f);
	getPointTarget(ToActorCharacter, start_point1, PointFinish); // paving a new path
	NextPointLocation(ToActorCharacter->GetActorLocation(), PointFinish);

}


FVector UShipNavMovementComponent::GetForwardVector(AActor* FromActor)
{
	FVector result = FVector(0.f, 0.f, 0.f);
	FVector ALocation = FromActor->GetActorLocation();
	for (int i = 0; i < 10; i++)
	{
		FVector start_point = CircumventionPoint(ToActorCharacter, PointCurrentTarget, 60.f, 300.0f);

		UE_LOG(LogTemp, Warning, TEXT("ABaseAIController::GetForwardVector  "));
	}
	return result;
}

FVector UShipNavMovementComponent::InFrontOfPoint(AActor* FromActor)
{
	// distance to the target when moving
	const int LongRange = 100;
	return (FromActor->GetActorForwardVector() * LongRange) + FromActor->GetActorLocation();
}

/**
* calculate where you can turn
*/
bool UShipNavMovementComponent::CircumventionPointRange(AActor* ToActor, FVector TargetV, float Agle, float RangeLong)
{

	//	UE_LOG(LogTemp, Warning, TEXT("ABaseAIController::CircumventionPointRange %f "), Agle);
	FVector  Loc = ToActor->GetActorLocation();

	//ABaseCharacter * Hero = *ToActor;
	ABaseCharacter * Hero = Cast<ABaseCharacter>(ToActor);
	if (Hero)
	{
		// Meshesd
	//	float ang = Hero->Meshesd->GetAngularDamping();
		float ang = 1.f;
		//		UE_LOG(LogTemp, Warning, TEXT("ABaseAIController::CircumventionPointRange ang %f "), ang);
	}


	FVector  Vc2 = UKismetMathLibrary::RotateAngleAxis(ToActor->GetActorForwardVector(), (360 - Agle), ToActor->GetActorUpVector());
	Vc2 = (Vc2 * RangeLong) + Loc;
	//DrawDebugLine(GetWorld(), Loc, Vc2, FColor(255, 200, 0), true, 1, 0, 6);
	float CurrentDistance_2 = FVector::Dist(TargetV, Vc2);
	bool t2 = TracePoint(ToActor, Loc, Vc2);
	if (!t2)
	{

		//	UE_LOG(LogTemp, Warning, TEXT("ABaseAIController::CircumventionPointRange true "));
		return true;
	}
	return false;
}



/**
* calculate where you can turn
*/
FVector UShipNavMovementComponent::CircumventionPoint(AActor* ToActor, FVector TargetV, float Agle, float RangeLong)
{
	//const float rang = 200.f;
	FVector  Loc = ToActor->GetActorLocation();

	FVector  Vc1 = UKismetMathLibrary::RotateAngleAxis(ToActor->GetActorForwardVector(), Agle, ToActor->GetActorUpVector());
	FVector  Vc2 = UKismetMathLibrary::RotateAngleAxis(ToActor->GetActorForwardVector(), (360 - Agle), ToActor->GetActorUpVector());

	Vc1 = (Vc1 * RangeLong) + Loc;
	Vc2 = (Vc2 * RangeLong) + Loc;
	//	DrawDebugLine(GetWorld(), Loc, Vc1, FColor(255, 0, 0), true, 10, 2, 6);
	//DrawDebugLine(GetWorld(), Loc, Vc2, FColor(255, 0, 0), true, 10, 2, 6);
	float CurrentDistance_1 = FVector::Dist(TargetV, Vc1);
	float CurrentDistance_2 = FVector::Dist(TargetV, Vc2);
	bool t1 = TracePoint(ToActor, Loc, Vc1);
	bool t2 = TracePoint(ToActor, Loc, Vc2);
	if (CurrentDistance_1 > CurrentDistance_2 && !t2)
	{
		return Vc2;
	}
	return Vc1;
} 




bool UShipNavMovementComponent::TracePoint(AActor* ActorIgnor, FVector  Start, FVector Finish)
{
	if (debug)
		DrawDebugLine(GetWorld(), Start, Finish, FColor(2, 90, 5), true, 6, 0, 2.44);
	const int Zh = 150;
	Start.Z = Zh;
	Finish.Z = Zh;
	//const EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::ForOneFrame;
	const EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::None;
	TArray< TEnumAsByte<EObjectTypeQuery> > ObjectTypes;
	TArray<FHitResult>  OutHits;
	ActorsToIgnore.Add(ActorIgnor);
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	return UKismetSystemLibrary::LineTraceMultiForObjects(GetWorld(), Start, Finish, ObjectTypes, false, ActorsToIgnore, DrawDebugType, OutHits, true);
}



void UShipNavMovementComponent::MoveActor()
{
	if (getDistancePoint() && EnableTickMove && GoMove)
	{
		MoveForce();
		MoveTorque();
	}
}



void UShipNavMovementComponent::GoMoveActor(AActor* ToActor)
{
	if (ToActor)
	{
	//	MoveToActor(ToActor, 10.f, true, true, true);
	}
}

void UShipNavMovementComponent::GoMoveLocation(FVector Location)
{
	//MoveToLocation(Location, .1f, true, true);
}



void UShipNavMovementComponent::AddNewPoint()
{
	if (CourseOnTarget.Num() > 0) {
		ToActorCharacter->GetActorLocation(); // controller
		PointCurrentTarget = CourseOnTarget[0];
	}
}




/**
* @param CharacterSingleFVector - cerrent character
* @param FVector StartLocation - start
* @param FVector FinishLocation - finish
*/
void UShipNavMovementComponent::SendPatrolTo(UPrimitiveComponent * Primitive, AActor* BaseCharacter, FVector Finish)
{
	if (debug)
		UE_LOG(LogTemp, Warning, TEXT("Start Patrol %f, %f, %f,"), Finish.X, Finish.Y, Finish.Z);
	BreakAI();
	PatrolTarget = true;
	GoMove = true;
	PrimitivePawn = Primitive;
	ToActorCharacter = BaseCharacter;
	//	UE_LOG(LogTemp, Warning, TEXT("Patrol To peat"));
	CharacterCurrentLocation = ToActorCharacter->GetActorLocation();
	indexZ = CharacterCurrentLocation.Z;

	PatrolStartLocation = ToActorCharacter->GetActorLocation(); // controller
	PatrolFinishLocation = Finish;// Repeat patroll
	PatrolFinishLocation.Z = indexZ; // Set current height

	PatrolPoint = PatrolFinishLocation;

	getPointTarget(BaseCharacter, CharacterCurrentLocation, PatrolPoint);

	NextPointLocation(CharacterCurrentLocation, PointFinish);
	EnableTickPatrol = true;
	//	UE_LOG(LogTemp, Warning, TEXT("Start Patrol %f, %f, %f,"), PatrolFinishLocation.X, PatrolFinishLocation.Y, PatrolFinishLocation.Z);
}


// LocationStartAndFinish
void UShipNavMovementComponent::TickPatrol()
{

	if (ToActorCharacter && EnableTickPatrol  && GoMove)
	{

		PatrolGetTarget();
		MoveForce();
		MoveTorque();
	}
}

bool UShipNavMovementComponent::PatrolGetTarget() {
	FVector ActorLocation = ToActorCharacter->GetActorLocation();

	GoMove = true;
	float CurrentDistance = FVector::Dist(PatrolPoint, ActorLocation);
	//	UE_LOG(LogTemp, Warning, TEXT("CurrentDistance %f"), CurrentDistance);
	//	UE_LOG(LogTemp, Warning, TEXT(" PatrolPoint %f %f %f"), PatrolPoint.X, PatrolPoint.Y, PatrolPoint.Z);
	if (CurrentDistance < 200)
	{
		//	UE_LOG(LogTemp, Warning, TEXT("< 200 dist: %f"), CurrentDistance);
		if (PatrolTarget) {
			PatrolPoint = PatrolStartLocation;
			UE_LOG(LogTemp, Warning, TEXT("PatrolLocation =<"));
		}
		else
		{
			//	UE_LOG(LogTemp, Warning, TEXT("PatrolLocation =>")); 
			PatrolPoint = PatrolFinishLocation;
		}
		getPointTarget(ToActorCharacter, ActorLocation, PatrolPoint);
		PatrolTarget = !PatrolTarget;
		//NextPointLocation();
	}
	//	UE_LOG(LogTemp, Warning, TEXT("%f"), CurrentDistance);
	return true;
}



void UShipNavMovementComponent::SendMoveActor(UPrimitiveComponent * Primitive, AActor* CharacterSingleFVector, FVector FinishLocation)
{

	//UE_LOG(LogTemp, Warning, TEXT("SendMoveActor %f %f"), FinishLocation.X, FinishLocation.Y);
	//	UE_LOG(LogTemp, Warning, TEXT("SendMoveActor "));

	BreakAI();
	CharacterCurrentLocation = CharacterSingleFVector->GetActorLocation();
	indexZ = CharacterCurrentLocation.Z;
	PrimitivePawn = Primitive;
	ToActorCharacter = CharacterSingleFVector;
	getPointTarget(ToActorCharacter, CharacterCurrentLocation, FinishLocation);

	NextPointLocation(CharacterCurrentLocation, FinishLocation);
	GoMove = true;
	EnableTickMove = true;
}


// LocationStartAndFinish
void UShipNavMovementComponent::NextPointLocation(FVector CurrentLocation, FVector FinishLocation)
{
	if (debug)
		UE_LOG(LogTemp, Warning, TEXT("Finish %f %f"), FinishLocation.X, FinishLocation.Y);
	const float  z = 0.f;
	CurrentLocation.Z = FinishLocation.Z = z;
	float d = FVector::Dist(CurrentLocation, FinishLocation);

	if (debug)
		UE_LOG(LogTemp, Warning, TEXT("go  %f"), d);

	if (CourseOnTarget.Num() > 0)
	{
		PointCurrentTarget = CourseOnTarget[0];
		CourseOnTarget.RemoveAt(0);
	}
	else {
		FinishLocation.Z = CurrentLocation.Z = z;
		if (d < 150)
		{
			if (debug)
				UE_LOG(LogTemp, Warning, TEXT("End move %f"), d);
			GoMove = false;
		}
	}
}





// LocationStartAndFinish
void UShipNavMovementComponent::BreakAI()
{
	EnableTickPatrol = false;
	EnableTickMove = false;
}


void UShipNavMovementComponent::MoveToPositionCharacter()
{
	if (ToActorCharacter)
	{
		//	GoMoveLocation(SendLocation);
	}
}



void UShipNavMovementComponent::MoveForce()
{
	if (PrimitivePawn && getDistancePoint() && GoMove)
	{
		//	UE_LOG(LogTemp, Warning, TEXT("ABaseAIController::MoveForce()"));
		FVector PrimitiveForwardVector = PrimitivePawn->GetForwardVector();
		float InRangeA = 200.f;
		float InRangeB = 10000.f;
		float OutRangeA = 13000.f;
		float OutRangeB = 135000.f;
		float RangeClamped = UKismetMathLibrary::MapRangeClamped(LenghtTarget, InRangeA, InRangeB, OutRangeA, OutRangeB);
		FVector ForceVector = PrimitiveForwardVector * RangeClamped;

		// add strength
		PrimitivePawn->AddForce(ForceVector);
	}
}
void UShipNavMovementComponent::MoveTorque()
{
	if (ToActorCharacter &&  getDistancePoint())
	{
		_getTForse();
	//	PrimitivePawn->AddTorque(FVector(0, 0, TForce), NAME_None, true);
	}
}


bool UShipNavMovementComponent::getDistancePoint()
{
	if (ToActorCharacter && GoMove)
	{
		FVector tmpV = ToActorCharacter->GetActorLocation();
		float CurrentDistance = FVector::Dist(PointCurrentTarget, ToActorCharacter->GetActorLocation());

		if (CurrentDistance > 150)
		{
			return ThereIsPoint = true;
		}
		else
		{

			TArray< TEnumAsByte<EObjectTypeQuery> > ObjectTypes;
			TArray<FHitResult>  OutHits;
			TArray<AActor*> ActorsToIgnore;

			const EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::None;
			const float BoxRadius = 150.f;
			//Orientation = FRotator(0.0f, 0.0f, 0.f);
			ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));


			bool Result = UKismetSystemLibrary::SphereTraceMultiForObjects(
				GetWorld(),
				PointCurrentTarget,
				ToActorCharacter->GetActorLocation(),
				BoxRadius,
				//Orientation,
				ObjectTypes,
				false,
				ActorsToIgnore,
				DrawDebugType,
				OutHits,
				true
			);

			NextPointLocation(PointCurrentTarget, ToActorCharacter->GetActorLocation());
		}
	}
	return false;
}



// private
void UShipNavMovementComponent::_getTForse()
{	//	UE_LOG(LogTemp, Warning, TEXT("MoveToPositionCharacter start"));

	const float tmpForse = 0.f;

	if (ToActorCharacter &&  getDistancePoint() && GoMove)
	{
		float TForce_tmp = TForce;

		float tmp_RotationFloat = 0.f;

		PointCurrentLocation = ToActorCharacter->GetActorLocation();
		PointCurrentCameraT = (ToActorCharacter->GetActorForwardVector()*1000.f) + PointCurrentLocation;

		Logic * ALogic = new Logic();
		ALogic->AngleCos(PointCurrentLocation, PointCurrentTarget, PointCurrentCameraT);
		float TAngle_tmp = ALogic->floatAngleCos;





		// from point
		FRotator FRotator_tmp = UKismetMathLibrary::FindLookAtRotation(PointCurrentLocation, PointCurrentTarget);
		FRotator ActorLocation = ToActorCharacter->GetActorRotation();
		// RotationFloat =
		//	tmp_RotationFloat = FRotator_tmp.Yaw + FRotatoractor_tmp.Yaw;

		// lead to a positive number
		if (ActorLocation.Yaw >= 0) {

		 
			if (FRotator_tmp.Yaw > 0) {


				if (FRotator_tmp.Yaw > ActorLocation.Yaw) {
					// all positive numbers
					tmp_RotationFloat = FRotator_tmp.Yaw - ActorLocation.Yaw;
					float tmp_RotationFloat2 = tmp_RotationFloat;
					//tmp_RotationFloat = 45 - tmp_RotationFloat;

					if (debug)
						UE_LOG(LogTemp, Warning, TEXT("Yaw1 = %f %f %f %f"), FRotator_tmp.Yaw, ActorLocation.Yaw, tmp_RotationFloat, tmp_RotationFloat2);


				}
				else {
					//tmp_RotationFloat = ActorLocation.Yaw- FRotator_tmp.Yaw ;
					tmp_RotationFloat = FRotator_tmp.Yaw - ActorLocation.Yaw;
					if (debug)
						UE_LOG(LogTemp, Warning, TEXT("Yaw2 = %f %f %f"), FRotator_tmp.Yaw, ActorLocation.Yaw, tmp_RotationFloat);
				}
			}
			else {




				if (FRotator_tmp.Yaw > ActorLocation.Yaw) {
					tmp_RotationFloat = FRotator_tmp.Yaw - ActorLocation.Yaw;
					if (debug)
						UE_LOG(LogTemp, Warning, TEXT("Yaw3 = %f %f %f"), FRotator_tmp.Yaw, ActorLocation.Yaw, tmp_RotationFloat);
				}
				else {
					//tmp_RotationFloat = ActorLocation.Yaw- FRotator_tmp.Yaw ; 


					tmp_RotationFloat = (ActorLocation.Yaw - FRotator_tmp.Yaw);
					float tmp_RotationFloat2 = tmp_RotationFloat;
					if (tmp_RotationFloat > 180) {
						tmp_RotationFloat = 360 - tmp_RotationFloat;
						if (debug)
							UE_LOG(LogTemp, Warning, TEXT("Yaw4 = %f %f %f %f"), FRotator_tmp.Yaw, ActorLocation.Yaw, tmp_RotationFloat, tmp_RotationFloat2);
					}
					else {
						// ships to the right
						// click to the up
						tmp_RotationFloat = (FRotator_tmp.Yaw - ActorLocation.Yaw);

						if (debug)
							UE_LOG(LogTemp, Warning, TEXT("Yaw5 = %f %f %f %f"), FRotator_tmp.Yaw, ActorLocation.Yaw, tmp_RotationFloat, tmp_RotationFloat2);
					}
				}
			}


		}
		else {

			if (FRotator_tmp.Yaw > 0) {
				if (FRotator_tmp.Yaw > ActorLocation.Yaw) {
					float tmp_RotationFloat2 = tmp_RotationFloat;
					if (tmp_RotationFloat > 180) {
						tmp_RotationFloat = FRotator_tmp.Yaw - ActorLocation.Yaw;
						tmp_RotationFloat = tmp_RotationFloat - 270;
						if (debug)
							UE_LOG(LogTemp, Warning, TEXT("Yaw6 = %f %f %f %f"), FRotator_tmp.Yaw, ActorLocation.Yaw, tmp_RotationFloat, tmp_RotationFloat2);
					}
					else {

						tmp_RotationFloat = FRotator_tmp.Yaw - ActorLocation.Yaw - 350;
						float tmp_RotationFloat2 = tmp_RotationFloat;
						if (debug)
							//Ship northeast, 
							UE_LOG(LogTemp, Warning, TEXT("Yaw7 = %f %f %f %f"), FRotator_tmp.Yaw, ActorLocation.Yaw, tmp_RotationFloat, tmp_RotationFloat2);
					}
				}
				else {
					tmp_RotationFloat = ActorLocation.Yaw - FRotator_tmp.Yaw;
					tmp_RotationFloat = FRotator_tmp.Yaw - ActorLocation.Yaw;

					float tmp_RotationFloat2 = tmp_RotationFloat;
					if (debug)
						UE_LOG(LogTemp, Warning, TEXT("Yaw8 = %f %f %f"), FRotator_tmp.Yaw, ActorLocation.Yaw, tmp_RotationFloat);
				}
			}
			else {
				if (FRotator_tmp.Yaw > ActorLocation.Yaw) {
					tmp_RotationFloat = FRotator_tmp.Yaw - ActorLocation.Yaw;
					float tmp_RotationFloat2 = tmp_RotationFloat;
					if (debug)
						UE_LOG(LogTemp, Warning, TEXT("Yaw9 = %f %f %f"), FRotator_tmp.Yaw, ActorLocation.Yaw, tmp_RotationFloat);
				}
				else {
					tmp_RotationFloat = ActorLocation.Yaw - FRotator_tmp.Yaw;


					tmp_RotationFloat = (ActorLocation.Yaw - FRotator_tmp.Yaw);
					if (tmp_RotationFloat > 180) {
						float tmp_RotationFloat2 = tmp_RotationFloat;
						tmp_RotationFloat = 180 - tmp_RotationFloat;
						if (debug)
							UE_LOG(LogTemp, Warning, TEXT("Yaw10= %f %f %f %f"), FRotator_tmp.Yaw, ActorLocation.Yaw, tmp_RotationFloat, tmp_RotationFloat2);
					}
					else {


						if (FRotator_tmp.Yaw > 0) {

							float tmp_RotationFloat2 = tmp_RotationFloat;
							tmp_RotationFloat = (ActorLocation.Yaw + FRotator_tmp.Yaw);

							if (-180 > tmp_RotationFloat) {
								tmp_RotationFloat = tmp_RotationFloat + 360;
								if (debug)
									UE_LOG(LogTemp, Warning, TEXT("Yaw11= %f %f %f %f"), FRotator_tmp.Yaw, ActorLocation.Yaw, tmp_RotationFloat, tmp_RotationFloat2);
							}
							else {
								if (debug)
									UE_LOG(LogTemp, Warning, TEXT("Yaw12= %f %f %f %f"), FRotator_tmp.Yaw, ActorLocation.Yaw, tmp_RotationFloat, tmp_RotationFloat2);

							}

						}
						else {


							float tmp_RotationFloat2 = tmp_RotationFloat;

							if (-180 > tmp_RotationFloat) {


								tmp_RotationFloat = (ActorLocation.Yaw + (FRotator_tmp.Yaw * -1)); 
								if (debug)
									UE_LOG(LogTemp, Warning, TEXT("Yaw13= %f %f %f %f"), FRotator_tmp.Yaw, ActorLocation.Yaw, tmp_RotationFloat, tmp_RotationFloat2);


							}
							else {
								tmp_RotationFloat = (ActorLocation.Yaw - FRotator_tmp.Yaw) * -90;
								if (debug)
									UE_LOG(LogTemp, Warning, TEXT("Yaw14= %f %f %f %f"), FRotator_tmp.Yaw, ActorLocation.Yaw, tmp_RotationFloat, tmp_RotationFloat2);

							}
						}

					}
				}
			}





			//tmp_RotationFloat = FRotator_tmp.Yaw - FRotatoractor_tmp.Yaw;
			//	tmp_RotationFloat = FRotatoractor_tmp.Yaw - FRotator_tmp.Yaw;

			//	tmp_RotationFloat = FRotator_tmp.Yaw - FRotatoractor_tmp.Yaw;

		}

		//	UE_LOG(LogTemp, Warning, TEXT(" Yaw1  = %f %f "), FRotator_tmp.Yaw, FRotatoractor_tmp.Yaw);




		float InRangeA = 0.f;
		float InRangeB = 365.f;
		float OutRangeA = 0.f;
		float OutRangeB = 4000.f;

		// where to turn
		//TForce =
		UKismetMathLibrary::MapRangeClamped(TAngle_tmp, InRangeA, InRangeB, OutRangeA, OutRangeB);

		if (90 >= tmp_RotationFloat && tmp_RotationFloat >= 0)
		{
			TForce = tmp_RotationFloat + (tmp_RotationFloat / 5);
			//	UE_LOG(LogTemp, Warning, TEXT(" 90 :   0 = %f %f "), tmp_RotationFloat, TForce); 
		}

		if (180 >= tmp_RotationFloat &&  tmp_RotationFloat >= 90)
		{
			TForce = tmp_RotationFloat + (tmp_RotationFloat / 2);
			//	UE_LOG(LogTemp, Warning, TEXT("180 :  90 = %f %f "), tmp_RotationFloat, TForce);
		}




		if (0 >= tmp_RotationFloat && tmp_RotationFloat >= -90)
		{
			TForce = tmp_RotationFloat + (tmp_RotationFloat / -5);
			//	UE_LOG(LogTemp, Warning, TEXT("   0: -90 = %f %f "), tmp_RotationFloat, TForce);
		}

		if (-90 > tmp_RotationFloat && tmp_RotationFloat >= -180)
		{
			TForce = tmp_RotationFloat + (tmp_RotationFloat / -2);
			//	UE_LOG(LogTemp, Warning, TEXT("-90 :-180 = %f %f "), tmp_RotationFloat, TForce); 
		}

		//	UE_LOG(LogTemp, Warning, TEXT("    :     = %f %f  %f %f"), FRotator_tmp.Yaw, FRotatoractor_tmp.Yaw, tmp_RotationFloat, TForce);


		if (tmp_RotationFloat > -1 && tmp_RotationFloat < 1)
		{
			//(LogTemp, Warning, TEXT("---------  %f  "), tmp_RotationFloat);
		}

		if (tmp_RotationFloat > 160) {
			TForce = 45;
			//UE_LOG(LogTemp, Warning, TEXT(" 120 ------ %f  "), tmp_RotationFloat);
		}
		if (tmp_RotationFloat < -160) {
			//UE_LOG(LogTemp, Warning, TEXT("-120 ------ %f  "), tmp_RotationFloat);
			TForce = -45;
		}


		ToActorCharacter->SetActorRotation(ActorLocation);

		//		UE_LOG(LogTemp, Warning, TEXT("---------= %f:%f "), tmp_RotationFloat, TForce);
		return;
	}
}

void UShipNavMovementComponent::getRotationAngularActor(FRotator FRotatorActor, float currentAngular, int32 different) {

	//if (TForce  < 0) {
	//TForce = TForce*(-1);
	TForce = currentAngular + (currentAngular / different);
	//}
	//else {
	//	TForce = currentAngular - (currentAngular / different); 
	//} 

}


void UShipNavMovementComponent::TraceForward(FVector start_point, FVector end_point)
{
}


void UShipNavMovementComponent::getPointTarget(AActor* Character, FVector start_point, FVector end_point)
{

	rec_log++; 

	if (rec_log > 4) {
		rec_log = 0;
		// something scary
		return;
	}

	if (!Finish_recursion)
	{ // recursion start
		if (debug)
			UE_LOG(LogTemp, Warning, TEXT("Building a route"));
		rec_log = 0;
		CourseOnTarget.Empty();
		Finish_recursion = true;
		PointFinish = end_point;
		//	UE_LOG(LogTemp, Warning, TEXT("=== %f %f %f ===="), start_point.X, start_point.Y, start_point.Z);
		//	UE_LOG(LogTemp, Warning, TEXT("=== %f %f %f ===="), end_point.X, end_point.Y, end_point.Z);
	}
	else {
		//	UE_LOG(LogTemp, Warning, TEXT("-s-- %f %f %f ---"), start_point.X, start_point.Y, start_point.Z);
		//	UE_LOG(LogTemp, Warning, TEXT("-e-- %f %f %f ---"), end_point.X, end_point.Y, end_point.Z);
	}

	TArray<FVector> dataPOINT; 
	//DrawDebugLine(GetWorld(), start_point, end_point, FColor(0, 102, 102), true, 6, 0, 2.33332);
	dataPOINT = SLT(Character, start_point, end_point);

	FVector dataOLD = start_point;

	// look at the number of points on the route
	if (dataPOINT.Num() > 0)
	{
		if (debug)
			UE_LOG(LogTemp, Warning, TEXT("go over the points that were found before"), rec_log);
		GoMove = true;
		// FVector TMP_dataV = start_point;



		for (int pointiter = 0; pointiter < dataPOINT.Num(); pointiter++)
		{

			FVector PointCurrent = dataPOINT[pointiter];
			 
			if (pointiter > 0)
			{
				//	FVector dataOLD = dataPOINT[pointiter-1];
			}

			FHitResult Hit = TracePoint_recurs(Character, dataOLD, PointCurrent);

			if (Hit.bBlockingHit)
			{


				//	DrawDebugSphere(GetWorld(), Hit.Location, 100, 8, FColor(255, 255, 0), false, 1, 0);

				// calculate the angle
				FVector VectorAngle = GetPoinAngel(dataOLD, Hit.Location, 0.4f);
				DrawDebugSphere(GetWorld(), VectorAngle, 250, 8, FColor(100, 100, 0), false, 1, 0);

				//	UE_LOG(LogTemp, Warning, TEXT("-y1-- %f %f %f ---"), VectorAngle.X, VectorAngle.Y, VectorAngle.Z);
				//
				FVector VectorAngleNew = ((VectorAngle - Hit.Location) * 500 + VectorAngle);

				DrawDebugSphere(GetWorld(), VectorAngleNew, 100, 8, FColor(180, 100, 100), false, 1, 0);

				//	UE_LOG(LogTemp, Warning, TEXT("-y2-- %f %f %f ---"), VectorAngleNew.X, VectorAngleNew.Y, VectorAngleNew.Z);
				FVector marsh_1 = ((ToActorCharacter->GetActorLocation() - Hit.Location)*300.f) + ToActorCharacter->GetActorLocation();
				marsh_1.Z = 0;

				DrawDebugSphere(GetWorld(), marsh_1, 290, 32, FColor(0, 100, 100), false, 1, 0);
				//	FVector  Vc1 = UKismetMathLibrary::RotateAngleAxis(break_lock, 90, dataV); 
				UE_LOG(LogTemp, Warning, TEXT("point %f %f "), marsh_1.X, marsh_1.Y);


				if (end_point != PointCurrent)
				{

					// See if we can add a new point.
					//	FHitResult Hit_new = TracePoint_recurs(Character, dataOLD, VectorAngleNew);
					UE_LOG(LogTemp, Warning, TEXT("find point "));
					getPointTarget(Character, VectorAngle, end_point);
			
					return;
				}
				else {
					//	UE_LOG(LogTemp, Warning, TEXT(" last point point 1 "));
					rec_log = 0;
					return;
				}
			}
			else
			{
				if (end_point == PointCurrent)
				{
					//	UE_LOG(LogTemp, Warning, TEXT(" last point point 2 "));
					rec_log = 0;

					Finish_recursion = false;
					return;
				}
				//
				//	UE_LOG(LogTemp, Warning, TEXT("Add a point where you can already go exactly when laying the path"));
				CourseOnTarget.Add(PointCurrent);

			}
			//	UE_LOG(LogTemp, Warning, TEXT("Blue colour %f %f  %f %f "), dataOLD.X, dataOLD.Y, PointCurrent.X, PointCurrent.Y);
			//DrawDebugLine(GetWorld(), dataOLD, PointCurrent, FColor(0, 0, 102), true, 6, 0, 2.33332);
			//TMP_dataV = PointCurrent;
		}
	}

	Finish_recursion = false;
	rec_log = 0;
}


/**
* just laying a route
*/

TArray<FVector> UShipNavMovementComponent::SLT(AActor* Character, FVector start_point, FVector end_point)
{
	//	UE_LOG(LogTemp, Warning, TEXT("from start_point to end_point"));
	TArray<FVector> dataN;
	end_point.Z = indexZ;

	//	UNavigationSystem* NavSys = UNavigationSystem::GetCurrent(GetWorld());
 	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld()); 
//
 	UNavigationPath* tpath = NavSys->FindPathToLocationSynchronously(GetWorld(), start_point, end_point);
	 
	//NavSys->RegisterNavigationInvoker(ToActorCharacter, 3000, 5000);
	//UNavigationPath *tpath = NavSys->FindPathToLocationSynchronously(GetWorld(), start_point, end_point);

	if (tpath != NULL && tpath->PathPoints.Num() > 0)
	{
		dataN = tpath->PathPoints;
		//	UE_LOG(LogTemp, Warning, TEXT("found points "));
	}

	return dataN;
}


FHitResult UShipNavMovementComponent::TracePoint_recurs(AActor* Character, FVector  Start, FVector Finish)
{
	ActorsToIgnore_trace.Empty();
	TArray<AActor*> Island;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseLand::StaticClass(), Island);

	for (int32 i = 0; i < Island.Num(); i++)
	{
		ActorsToIgnore_trace.Add(Island[i]);
	}


	const int Zh = 0.f;
	Finish.Z = Start.Z = Zh;

	//	const EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::ForDuration;

	const EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::None;

	TArray< TEnumAsByte<EObjectTypeQuery> > ObjectTypes;
	FHitResult  OutHit;
	ActorsToIgnore_trace.Add(Character);
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	//	UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), Start, Finish, ObjectTypes, false, ActorsToIgnore_trace, DrawDebugType, OutHit, true);

	return OutHit;
}