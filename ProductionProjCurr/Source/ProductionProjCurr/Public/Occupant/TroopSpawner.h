// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "gameMode/Enum_PlayerSide.h"
#include "TroopSpawner.generated.h"

class ABG_Tile;
class UData_PlayerSetUp;
class AOccupant_BaseClass;
class ATurnManager;

UCLASS()
class PRODUCTIONPROJCURR_API ATroopSpawner : public AActor
{
	GENERATED_BODY()

public:
	ATroopSpawner();

	void Initialize(
		ATurnManager*				InTurnManager,
		TMap<FIntPoint, ABG_Tile*>* InTileMap);

	void SpawnTroop(TSubclassOf<AOccupant_BaseClass> Occupant, ABG_Tile* Tile);
	void SpawnTroop(TSubclassOf<AOccupant_BaseClass> Occupant, ABG_Tile* Tile, EActivePlayerSide OwningPlayer);
	void SpawnStartingTroops(const TArray<TArray<ABG_Tile*>>& TileGrid, int32 Cols, int32 Rows);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Troop | Spawning")
	TSubclassOf<AOccupant_BaseClass> StartingTroopClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Troop | Spawning")
	float TroopSpawnHeight = 20.0f;

private:
	UPROPERTY()
	ATurnManager* TurnManager = nullptr;

	TMap<FIntPoint, ABG_Tile*>* TileMapPtr = nullptr;
};