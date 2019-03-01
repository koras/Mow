// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "PushForce.h"

#define LOCTEXT_NAMESPACE "FPushForceModule"

void FPushForceModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FPushForceModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}


void FPushForceModule::SendPatrolTo(UPrimitiveComponent * Primitive, AActor* BaseCharacter, FVector Finish)
{

}

void FPushForceModule::SendMoveActor(UPrimitiveComponent * Primitive, AActor* CharacterSingleFVector, FVector FinishLocation)
{

}


//void FPushForceModule::Tick(float DeltaSeconds) {

//}
// Called every frame
//void  FPushForceModule::Tick(float DeltaTime)
//{
	//Super::Tick(DeltaTime);
	//MoveToPositionCharacter();
////	MoveActor();
	//TickPatrol();
//}


int32 FPushForceModule::IsThisNumber42()
{
	int32 num = 3333;
	return num;
}
// LocationStartAndFinish
void  FPushForceModule::NextPointLocation(FVector CurrentLocation, FVector FinishLocation)
{
	if (debag)
		UE_LOG(LogTemp, Warning, TEXT("Finish %f %f"), FinishLocation.X, FinishLocation.Y);
	const float  z = 0.f;
	CurrentLocation.Z = FinishLocation.Z = z;
	float d = FVector::Dist(CurrentLocation, FinishLocation);

	if (debag)
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
			if (debag)
				UE_LOG(LogTemp, Warning, TEXT("End move %f"), d);
			GoMove = false;
		}
	}
}


bool FPushForceModule::TracePoint(AActor* ActorIgnor, FVector  Start, FVector Finish)
{
	//if (debag)
	//	DrawDebugLine(GetWorld(), Start, Finish, FColor(2, 90, 5), true, 6, 0, 2.44);
	const int Zh = 150;
	Start.Z = Zh;
	Finish.Z = Zh;
	//const EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::ForOneFrame;
	const EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::None;
	TArray< TEnumAsByte<EObjectTypeQuery> > ObjectTypes;
	TArray<FHitResult>  OutHits;
	ActorsToIgnore.Add(ActorIgnor);
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	return UKismetSystemLibrary::LineTraceMultiForObjects(Word -> GetWorld(), Start, Finish, ObjectTypes, false, ActorsToIgnore, DrawDebugType, OutHits, true);
}

void FPushForceModule::AddNewPoint()
{
	if (CourseOnTarget.Num() > 0) {
		ToActorCharacter->GetActorLocation(); // controller
		PointCurrentTarget = CourseOnTarget[0];
	}
}

void FPushForceModule::CheckPoint() {

	if (GoMove && ToActorCharacter) {
		
		FVector CurrentLocation = ToActorCharacter->GetActorLocation();
		
		FVector tmpForwardVector = ToActorCharacter->GetActorForwardVector();

		FVector tmpCurrentLocation = CurrentLocation;
		// Long Point
		float LongDistance = FVector::Dist(CurrentLocation, PointFinish);


		//	UE_LOG(LogTemp, Warning, TEXT("CurrentLocation %f %f %f "), CurrentLocation.Z, CurrentLocation.Y, CurrentLocation.X);
		float CurrentDistance = FVector::Dist(CurrentLocation, CheckPointOLD);
		float newRange = FVector::Dist(CurrentLocation, PointFinish);	



																
		if (CurrentDistance <= iDistanceMin) {




			FVector start_point = CircumventionPoint(ToActorCharacter, PointCurrentTarget, 90.0f, 400.0f);
			getPointTarget(ToActorCharacter, start_point, PointFinish);
			NextPointLocation(CurrentLocation, PointFinish);
			//	UE_LOG(LogTemp, Warning, TEXT("CurrentDistance %f"), CurrentDistance);
			CheckPointOLD = CurrentLocation;
			OldRange = newRange;
			return;
		}


		if (LongDistance >= iDistanceMax)
		{
			

			if (
				TracePoint(
					ToActorCharacter,
					CurrentLocation, 
					InFrontOfPoint(ToActorCharacter)
				)
				)
			{
				 
			
			//	float ForceСrutch = 90.f;

				FVector PrimitiveForwardVector = PrimitivePawn->GetForwardVector();
		
				float InRangeA = -200.f;
				float InRangeB = -10000.f;
				float OutRangeA = -13000.f;
				float OutRangeB = -150000.f;
				float RangeClamped = UKismetMathLibrary::MapRangeClamped(LenghtTarget, InRangeA, InRangeB, OutRangeA, OutRangeB);
				//FVector ForceVector = PrimitiveForwardVector * OutRangeB;
				FVector ForceVector = FVector(PrimitiveForwardVector.X * OutRangeB, PrimitiveForwardVector.Y * OutRangeB, 0);
		//		UE_LOG(LogTemp, Warning, TEXT("========== %f  %f  "), ForceVector.X, ForceVector.Y);
			
				//	PrimitivePawn->AddForce(ForceVector); 
				FRotator rt = ToActorCharacter->GetActorRotation();

				ToActorCharacter->SetActorRotation(FRotator(rt.Pitch + 180, rt.Yaw + 180, 0));
				const float  grad = 60.0f;
				//	FVector start_point1 = CircumventionPoint(ToActorCharacter, PointCurrentTarget, grad, 350.0f); 
				bool getPoint = false;

				PointCurrentCameraT = (ToActorCharacter->GetActorForwardVector()*1000.f) + ToActorCharacter->GetActorLocation();


				FHitResult  OutHit = TracePoint_recurs(ToActorCharacter, ToActorCharacter->GetActorLocation(), PointFinish);


				tmpCurrentLocation = GetPoinAngel(OutHit.Location, ToActorCharacter->GetActorLocation(), 1);






				getPointTarget(ToActorCharacter, tmpCurrentLocation, PointFinish); 
				NextPointLocation(CurrentLocation, PointFinish);

				OldRange = newRange;
			}
			else {


				if (debag)
					UE_LOG(LogTemp, Warning, TEXT("stop"));
				//	UE_LOG(LogTemp, Warning, TEXT("1stop  %f %f %f %f"), newRange, OldRange, CurrentDistance, LongDistance);

				if (newRange > OldRange + iDistanceMin)
				{


					///	UE_LOG(LogTemp, Warning, TEXT("2stop  newRange , OldRange, CurrentDistance %f %f %f %f"), newRange, (OldRange + iDistanceMin), OldRange, CurrentDistance);

					//	getPointTarget(ToActorCharacter, start_point1, PointFinish); 
					NextPointLocation(CurrentLocation, PointFinish);

				}
			}
			OldRange = newRange;
			//	UE_LOG(LogTemp, Warning, TEXT("CurrentDistance %f"), CurrentDistance);
		}

		CheckPointOLD = CurrentLocation;
	}
}




void FPushForceModule::getPointTarget(AActor* Character, FVector start_point, FVector end_point)
{

	rec_log++;


	if (rec_log > 4) {
		rec_log = 0;

		return;
	}

	if (!Finish_recursion)
	{ 

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


	if (dataPOINT.Num() > 0)
	{ 
		GoMove = true;
		// FVector TMP_dataV = start_point;



		for (int pointiter = 0; pointiter < dataPOINT.Num(); pointiter++)
		{

			FVector PointCurrent = dataPOINT[pointiter];
			// путь
			if (pointiter > 0)
			{
				//	FVector dataOLD = dataPOINT[pointiter-1];
			}

			FHitResult Hit = TracePoint_recurs(Character, dataOLD, PointCurrent);

			if (Hit.bBlockingHit)
			{


				//	DrawDebugSphere(GetWorld(), Hit.Location, 100, 8, FColor(255, 255, 0), false, 1, 0);
				 
				FVector VectorAngle = GetPoinAngel(dataOLD, Hit.Location, 0.4f);
				DrawDebugSphere(Word->GetWorld(), VectorAngle, 250, 8, FColor(100, 100, 0), false, 1, 0);


				//
				FVector VectorAngleNew = ((VectorAngle - Hit.Location) * 500 + VectorAngle);

				DrawDebugSphere(Word->GetWorld(), VectorAngleNew, 100, 8, FColor(180, 100, 100), false, 1, 0);


				FVector marsh_1 = ((ToActorCharacter->GetActorLocation() - Hit.Location)*300.f) + ToActorCharacter->GetActorLocation();
				marsh_1.Z = 0;

				DrawDebugSphere(Word->GetWorld(), marsh_1, 290, 32, FColor(0, 100, 100), false, 1, 0);
				//	FVector  Vc1 = UKismetMathLibrary::RotateAngleAxis(break_lock, 90, dataV); 
			


				if (end_point != PointCurrent)
				{
					 
					//	FHitResult Hit_new = TracePoint_recurs(Character, dataOLD, VectorAngleNew);

					getPointTarget(Character, VectorAngle, end_point);
			
					return;
				}
				else {

					rec_log = 0;
					return;
				}
			}
			else
			{
				if (end_point == PointCurrent)
				{

					rec_log = 0;

					Finish_recursion = false;
					return;
				}
				//

				CourseOnTarget.Add(PointCurrent);

			}

			//DrawDebugLine(GetWorld(), dataOLD, PointCurrent, FColor(0, 0, 102), true, 6, 0, 2.33332);
			//TMP_dataV = PointCurrent;
		}
	}

	Finish_recursion = false;
	rec_log = 0;
}

FHitResult FPushForceModule::TracePoint_recurs(AActor* Character, FVector  Start, FVector Finish)
{
	ActorsToIgnore_trace.Empty();
	TArray<AActor*> Island;
//	UGameplayStatics::GetAllActorsOfClass(Word->GetWorld(), AIslandSingle::StaticClass(), Island);

//	for (int32 i = 0; i < Island.Num(); i++)
//	{
	//	ActorsToIgnore_trace.Add(Island[i]);
//	}


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

FVector FPushForceModule::GetPoinAngel(FVector Center, FVector Ship, float alpha) {
	if (debag)
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


void  FPushForceModule::MoveGo()
{
	GoMove = false;
	FVector start_point1 = CircumventionPoint(ToActorCharacter, PointCurrentTarget, 60, 350.f);
	getPointTarget(ToActorCharacter, start_point1, PointFinish); // прокладываем новый путь
	NextPointLocation(ToActorCharacter->GetActorLocation(), PointFinish);

}


/**
* вычисляем куда можно повернуть
*/
bool FPushForceModule::CircumventionPointRange(AActor* ToActor, FVector TargetV, float Agle, float RangeLong)
{

	//	UE_LOG(LogTemp, Warning, TEXT("ABaseAIController::CircumventionPointRange %f "), Agle);
	FVector  Loc = ToActor->GetActorLocation();

	//ABaseCharacter * Hero = *ToActor;
	ABaseCharacter * Hero = Cast<ABaseCharacter>(ToActor);
	if (Hero)
	{
		// Meshesd
		float ang = Hero->Meshesd->GetAngularDamping();
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
FVector FPushForceModule::GetForwardVector(AActor* FromActor)
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


FVector FPushForceModule::InFrontOfPoint(AActor* FromActor)
{
	// растояние до цели при движении
	const int LongRange = 100;
	return (FromActor->GetActorForwardVector() * LongRange) + FromActor->GetActorLocation();
}
#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPushForceModule, PushForce)