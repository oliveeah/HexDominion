// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "gameMode/Enum_PlayerSide.h"
#include "EndGameLogic.generated.h"

class ABG_Tile;
class ATileManager;
class ATurnManager;
class UTileSpawner_Data;

UCLASS()
class PRODUCTIONPROJCURR_API UEndGameLogic : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(
		ATileManager*	   InTileManager,
		ATurnManager*	   InTurnManager,
		UTileSpawner_Data* InSpawnerData);

	// Called when end phase begins — spawns the cornucopia tile at grid centre
	void SpawnCornucopia();

	// Called each end-phase round — checks who holds the cornucopia
	void EvaluateHoldCondition(int32 CurrentTurn);

	UPROPERTY(EditAnywhere, Category = "End Game")
	int32 TurnsRequiredToWin = 3;

private:
	ATileManager*	   TileManager = nullptr;
	ATurnManager*	   TurnManager = nullptr;
	UTileSpawner_Data* SpawnerData = nullptr;

	ABG_Tile* CornucopiaTile = nullptr;

	EActivePlayerSide HoldingPlayer = EActivePlayerSide::None;
	int32			  HoldTurnCount = 0;
};
