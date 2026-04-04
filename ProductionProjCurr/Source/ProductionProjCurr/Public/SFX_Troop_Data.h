// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Sound/SoundBase.h"
#include "SFX_Troop_Data.generated.h"

USTRUCT(BlueprintType)
struct FTroopSFX
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SFX")
	USoundBase* DeathSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SFX")
	USoundBase* AttackSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SFX")
	USoundBase* HitSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SFX")
	USoundBase* SpawnSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SFX")
	USoundBase* MoveSound = nullptr;
};

UCLASS()
class PRODUCTIONPROJCURR_API USFX_Troop_Data : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FTroopSFX FTroopSFX_PlayerA;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FTroopSFX FTroopSFX_PlayerB;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FTroopSFX FTroopSFX_PlayerC;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FTroopSFX FTroopSFX_PlayerD;
};
