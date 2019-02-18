// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h" 
#include "Kismet/GameplayStatics.h"
#include "Platform/PlatformCamera.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"


#include "ManagerCamera.generated.h"



USTRUCT()
struct FCameraFixSpringArm
{
	GENERATED_USTRUCT_BODY()

	FVector Min;
	FVector Max;
};



UCLASS()
class MOW_API AManagerCamera : public APawn
{
	GENERATED_BODY()

public:

	UStaticMeshComponent * Fly;

	// Sets default values for this pawn's properties
	AManagerCamera();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FCameraFixSpringArm CameraFixSpringArm;
	float CameraFix;

	//UPROPERTY(EditAnywhere, Category = "Mcamers")
	//USceneComponent * RootComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fraction")
		float Fraction;


	UPROPERTY(EditAnywhere, Category = "Mcamers")
		UCameraComponent* OurCamera;

	UPROPERTY(EditAnywhere, Category = "Mcamers")
		USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = "Mcamers")
		USceneComponent* OurVisibleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mcamers")
		USpringArmComponent* OurCameraSpringArm;

	//Input variables
	FVector CurrentVelocity;
	bool bGrowing;
	bool CameraMove;
	// move camera
	FVector CameraMoveStart;
	FVector CameraMoveFinish;
	FVector CameraMoveCalc;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void MiddleMouseStart();
	void MiddleMouseStop();
	void MiddleRollerFunc(float Value);
	void NewLocationCameraTick(FVector NewLocation);

	void MoveToLocationCamera();
	void CameraGrow(float DeltaTime);
	void CameraMoveXY(float DeltaTime);
	void traceCamera(FVector Start);

	UPROPERTY(EditAnywhere, Category = "Camera", BlueprintReadWrite)
		float CameraHeight;
	FColor color = FColor(200, 200, 200);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
