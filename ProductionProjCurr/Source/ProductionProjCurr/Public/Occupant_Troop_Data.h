// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Animation/AnimInstance.h"
#include "Occupant_Troop_Data.generated.h"

USTRUCT(BlueprintType)
struct FTeamVisualData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMesh* Mesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UAnimInstance> AnimClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Scale = 1.0f;
};
UCLASS()
class PRODUCTIONPROJCURR_API UOccupant_Troop_Data : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FTeamVisualData FTeamVisualData_PlayerA;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FTeamVisualData FTeamVisualData_PlayerB;
	
		UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FTeamVisualData FTeamVisualData_PlayerC;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FTeamVisualData FTeamVisualData_PlayerD;
};
