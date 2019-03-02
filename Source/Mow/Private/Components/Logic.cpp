// Fill out your copyright notice in the Description page of Project Settings.

#include "Logic.h"

Logic::Logic()
{
}

Logic::~Logic()
{
}
void Logic::Switch()
{
	floatAngleCos = 0.f;
}

void Logic::AngleCos(FVector Av, FVector Bv, FVector Cv) {

	float Ax = Av.X;
	float Ay = Av.Y;
	float Bx = Bv.X;
	float By = Bv.Y;
	float Cx = Cv.X;
	float Cy = Cv.Y;

	float ABx = Bx - Ax;
	float ABy = By - Ay;
	float ACx = Cx - Ax;
	float ACy = Cy - Ay;

	float ABxACx = ABx*ACx;
	float AByACy = ABy*ACy;
	float ABxACx_AByACy = ABxACx + AByACy;

	float moduls = (FMath::Sqrt((ABx*ABx) + (ABy*ABy))) * (FMath::Sqrt((ACx*ACx) + (ACy*ACy)));
	float truAngle = ABxACx_AByACy / moduls;

	floatAngleCos = (180.f) / PI * FMath::Acos(truAngle);

}