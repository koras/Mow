// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class MOW_API Logic
{
public:
	Logic();
	~Logic();


	float floatAngleCos;

	void AngleCos(FVector Av, FVector Bv, FVector Cv);

	void Switch();
};
