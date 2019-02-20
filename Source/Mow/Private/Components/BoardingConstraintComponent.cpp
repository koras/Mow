// Fill out your copyright notice in the Description page of Project Settings.

#include "BoardingConstraintComponent.h"

void UBoardingConstraintComponent::RemovingIslandAbordage()
{


}
// who pulls
// who are pulling
void UBoardingConstraintComponent::startAbordage(AActor * whoPulls, AActor * whoArePulling)
{
	//if (!IsLand)return;
	UE_LOG(LogTemp, Warning, TEXT("void ABaseCharacter::ConstraintActor() 1"));
	//if (IsLand->bMove && IsLand->bHeroes_Island == false && bIsAbordage == false) {
	UE_LOG(LogTemp, Warning, TEXT("void ABaseCharacter::ConstraintActor() 2"));
	//	ConstraintComp = NewObject<UPhysicsConstraintComponent>(this);

//	ConstraintComp = *(this);
	// https://wiki.unrealengine.com/Physics_Constraints,_Create_New_Constraints_Dynamically_During_Runtime
	// https://answers.unrealengine.com/questions/436450/creating-a-new-physics-constraint-component-in-c-c.html
	//if (IsLand && WeaponMesh && bConstraintComp) {


		//UPrimitiveComponent* ConstraintComponent_1 = whoPulls;
	//	UPrimitiveComponent* ConstraintComponent_2 = whoArePulling->prmi;

	(this)->OnComponentCreated();
	//			ConstraintComp->AttachToComponent(WeaponMesh, NAME_None, EAttachLocation::KeepWorldPosition);
//	(this)->SetWorldLocation(GetActorLocation());
	(this)->RegisterComponent();

	(this)->ConstraintActor1 = whoPulls;
	(this)->ConstraintActor2 = whoArePulling;
	(this)->ComponentName1.ComponentName = NAME_None;
	(this)->ComponentName2.ComponentName = NAME_None;
	(this)->ConstraintInstance.ConstraintBone1 = NAME_None;
	(this)->ConstraintInstance.ConstraintBone2 = NAME_None;

	(this)->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0.f);
	(this)->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0.f);
	(this)->SetLinearZLimit(ELinearConstraintMotion::LCM_Limited, 0.f);
	(this)->SetLinearVelocityTarget(FVector(0, 0, 300));
	//ConstraintInstance.LinearVelocityTarget = FVector(0, 0, 300);
	(this)->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Free, 0.f);
	(this)->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Free, 0);
	(this)->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Free, 0);

	(this)->SetDisableCollision(true);
	//	(this)->SetConstrainedComponents(WeaponMesh, NAME_None, ConstraintComponent_2, NAME_None);
	(this)->UpdateConstraintFrames();

	//	bConstraintComp = false;
	bIsLandBoarding = true;
	//	bIsAbordage = true;
	HUDabordage = true;

	//	IsLand->StartAbordage();
	//	IsLand->StopMove();
	//	IsLand->bMove = true;
		//	IsLand->Heroes_Island = this;
		//IsLand->bHeroes_Island = true;
	UE_LOG(LogTemp, Warning, TEXT("Object is abordage"));
	//bBusy = true;
	//MoveBreck();
//	}
//}
//	else {
//		UE_LOG(LogTemp, Warning, TEXT(" 1 %s"), *IsLand->GetName());
//	}
}

void UBoardingConstraintComponent::stopAbordage()
{


	(this)->RemoveFromRoot();
	(this)->BreakConstraint();
	(this)->DestroyComponent(true);
	HUDabordage = false;
	//	SelectEraseToBoarding = false;
	//	bConstraintComp = true;
	bIsLandBoarding = true;
	//	bIsAbordage = false;

	//	IsLand->BreackAbordage();
	//	IsLand->bHeroes_Island = false;


	//	bBusy = false;

	//	SetNewLocation(GetActorLocation() + GetActorForwardVector()*300.f);
		//	UE_LOG(LogTemp, Warning, TEXT("delete component"));
	//}
}
