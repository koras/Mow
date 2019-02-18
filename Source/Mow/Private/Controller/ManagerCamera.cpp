// Fill out your copyright notice in the Description page of Project Settings.

#include "ManagerCamera.h"

// Sets default values
AManagerCamera::AManagerCamera()
{
	//	Fraction = GetWorld()->GetFirstPlayerController()->PlayerState->PlayerId;
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraHeight = 1000.0f;
	CameraFix = 1000.0f;
	CameraFixSpringArm.Max = FVector(12388.f, 10000.0f, 1500.f);
	CameraFixSpringArm.Min = FVector(-15610.0f, -6050.0f, 500.f);
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0; 




	OurCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	USceneComponent * RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCamera"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyVisible"));

	 
	OurVisibleComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);


//	static ConstructorHelpers::FObjectFinder <UStaticMesh>StaticMesh(TEXT("StaticMesh'/Game/Platform/Platform.Platform'"));
 


	 
	OurCameraSpringArm->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	OurCameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, CameraHeight), FRotator(-61.0f, 0.0f, 0.0f));
	OurCameraSpringArm->TargetArmLength = CameraHeight;
	OurCameraSpringArm->bEnableCameraLag = false;

	 
	 
//	OurCamera->AttachTo(OurCameraSpringArm);
	OurCamera->AttachToComponent(OurCameraSpringArm, FAttachmentTransformRules::KeepWorldTransform);
	OurCamera->FieldOfView = 90.f;
	 
	 
	CameraMove = false;

}

// Called when the game starts or when spawned
void AManagerCamera::BeginPlay()
{
	Super::BeginPlay();
	NewLocationCameraTick(GetActorLocation());
}

// Called every frame
void AManagerCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector dataCamera = GetActorLocation();
	CameraGrow(DeltaTime);
	CameraMoveXY(DeltaTime);
	MoveToLocationCamera();
}

// Called to bind functionality to input
void AManagerCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AManagerCamera::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AManagerCamera::MoveRight);
	PlayerInputComponent->BindAxis("MiddleRoller", this, &AManagerCamera::MiddleRollerFunc);
	PlayerInputComponent->BindAction("MiddleMouse", IE_Pressed, this, &AManagerCamera::MiddleMouseStart);
	PlayerInputComponent->BindAction("MiddleMouse", IE_Released, this, &AManagerCamera::MiddleMouseStop);
}


// Handle growing and shrinking based on our "Grow" action
void AManagerCamera::CameraGrow(float DeltaTime)
{
	float CurrentScale = OurVisibleComponent->GetComponentScale().X;
	if (bGrowing)
	{
		// Grow to double size over the course of one second
		CurrentScale += DeltaTime;
	}
	else
	{
		// Shrink half as fast as we grow
		CurrentScale -= (DeltaTime * 0.5f);
	}
	// Make sure we never drop below our starting size, or increase past double size.
	CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);
	OurVisibleComponent->SetWorldScale3D(FVector(CurrentScale));
}

// Handle movement based on our "MoveX" and "MoveY" axes
void AManagerCamera::CameraMoveXY(float DeltaTime)
{
	if (!CurrentVelocity.IsZero())
	{ 
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		UE_LOG(LogTemp, Warning, TEXT("AManagerCamera::CameraMoveXY11  %f   %f  %f"), NewLocation.X, NewLocation.Y, NewLocation.Z);
		NewLocationCameraTick(NewLocation);
	}else{

	//	UE_LOG(LogTemp, Warning, TEXT("AManagerCamera::CameraMoveXY00  %f   %f  %f"), CameraMoveStart.X, CameraMoveStart.Y, CameraMoveStart.Z); 
	
	}
}



void AManagerCamera::MiddleRollerFunc(float Value)
{
	CameraHeight = CameraHeight + Value*150.f;
	CameraHeight = FMath::Clamp(CameraHeight, CameraFixSpringArm.Min.Z, CameraFixSpringArm.Max.Z);
	OurCameraSpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, CameraHeight));
}



void AManagerCamera::MiddleMouseStart()
{
	CameraMove = true;

	TArray< TEnumAsByte< EObjectTypeQuery > > ObjectTypes;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery1);

	FHitResult HitResult;
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	controller->GetHitResultUnderCursor(ECC_Pawn, true, HitResult);
	CameraMoveStart = HitResult.Location;
	 
	UE_LOG(LogTemp, Warning, TEXT("AManagerCamera::MiddleMouseStart  %f   %f  %f"), CameraMoveStart.X, CameraMoveStart.Y, CameraMoveStart.Z);

//	UE_LOG(LogTemp, Warning, TEXT(" CameraMoveStart %f   %f  %f"), CameraMoveStart.X, CameraMoveStart.Y, CameraMoveStart.Z);
//	UE_LOG(LogTemp, Warning, TEXT(" HitResult %s"), *HitResult.GetActor()->GetName());
	traceCamera(CameraMoveStart);
}


void AManagerCamera::MiddleMouseStop()
{
	CameraMove = false;
	UE_LOG(LogTemp, Warning, TEXT("AManagerCamera::MiddleMouseStop  %f   %f  %f"), CameraMoveStart.X, CameraMoveStart.Y, CameraMoveStart.Z);
}



/**
* Move Camera
*/
void AManagerCamera::MoveToLocationCamera() {
	
	if (CameraMove) {
		FHitResult HitResult;
		APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		controller->GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, true, HitResult);
		CameraMoveFinish = HitResult.Location;
		CameraMoveCalc = GetActorLocation() - (CameraMoveFinish - CameraMoveStart);
		NewLocationCameraTick(CameraMoveCalc);
	}
	
}

void AManagerCamera::traceCamera(FVector Start) {
	//	FVector End = Start;
	//End.Z = Start.Z - 4000;
	
	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	RV_TraceParams.bTraceComplex = true;
	RV_TraceParams.bTraceAsyncScene = true;
	RV_TraceParams.bReturnPhysicalMaterial = false;

	//Re-initialize hit info
	FHitResult RV_Hit(ForceInit);

	//call GetWorld() from within an actor extending class

	if (RV_Hit.bBlockingHit) {
		if (RV_Hit.GetActor()->IsA(APlatformCamera::StaticClass()))
		{
		//	APlatformFly* Point = Cast(RV_Hit.GetActor());
			//if (!HitCharacter) return;

			//do stuff to the HitCharacter
		}
	}
}


void AManagerCamera::MoveForward(float Value)
{
	CurrentVelocity.X = FMath::Clamp(Value, -1.0f, 1.0f) * 100.0f;
	//UE_LOG(LogTemp, Warning, TEXT("AManagerCamera::Move_Forward %f   %f  %f"), CurrentVelocity.X, CurrentVelocity.Y, CurrentVelocity.Z);
}

void AManagerCamera::MoveRight(float Value)
{
	CurrentVelocity.Y = Value*100.0f;
	//UE_LOG(LogTemp, Warning, TEXT("AManagerCamera::MoveRight %f   %f  %f"), CurrentVelocity.X, CurrentVelocity.Y, CurrentVelocity.Z);
}


void AManagerCamera::NewLocationCameraTick(FVector NewLocation)
{
	NewLocation.Z = CameraFix; // the camera is always on the spot
	NewLocation.Y = FMath::Clamp(NewLocation.Y, CameraFixSpringArm.Min.Y, CameraFixSpringArm.Max.Y);
	NewLocation.X = FMath::Clamp(NewLocation.X, CameraFixSpringArm.Min.X, CameraFixSpringArm.Max.X);

	UE_LOG(LogTemp, Warning, TEXT("AManagerCamera::NewLocationCameraTick NewLocation %f   %f  %f"), NewLocation.X, NewLocation.Y, NewLocation.Z);
	SetActorLocation(NewLocation);
}