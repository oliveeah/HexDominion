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

	void SpawnCornucopia();

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
