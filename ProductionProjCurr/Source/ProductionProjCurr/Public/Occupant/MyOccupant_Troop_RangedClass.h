// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Occupant/Occupant_Troop_BaseClass.h"
#include "MyOccupant_Troop_RangedClass.generated.h"

UCLASS()
class PRODUCTIONPROJCURR_API AMyOccupant_Troop_RangedClass : public AOccupant_Troop_BaseClass
{
	GENERATED_BODY()

public:
	AMyOccupant_Troop_RangedClass();

	virtual ETroopType GetTroopType() const override { return ETroopType::Ranged; }
};
