// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Noise/FastNoiseLite.h"
#include "Tile_PathLogic.generated.h"

class ABG_Tile;
class ATileManager;
class UTileSpawner_Data;

UCLASS()
class PRODUCTIONPROJCURR_API UTile_PathLogic : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(
		TArray<TArray<ABG_Tile*>>* InTileGrid,
		UTileSpawner_Data* InData,
		ATileManager* InTileManager,
		FRandomStream* InRandomStream,
		UWorld* InWorld,
		AActor* InOwner);

	void SpawnPaths();
	void PlacePlayerSpawnTeleporters();

private:
	TArray<TArray<ABG_Tile*>>* TileGrid    = nullptr;
	UTileSpawner_Data*          TileSpawnerData = nullptr;
	ATileManager*               TileManager    = nullptr;
	FRandomStream*              RandomStream   = nullptr;
	UWorld*                     World          = nullptr;
	AActor*                     Owner          = nullptr;

	// Path generation
	bool TryBuildRandomPath(TArray<FIntPoint>& OutPath);
	void ChangeTileToPath(const FIntPoint& Coords);
	bool WouldIsolateTile(const FIntPoint& CandidatePathTile, const TSet<FIntPoint>& CurrentPathSet) const;

	// Teleporter placement
	void PlaceTeleporter(const FIntPoint& Coords);

	// Shared helpers
	ABG_Tile* SpawnTile(TSubclassOf<ABG_Tile> TileClass, const FTransform& Transform);
	void      ApplyNoiseHue(ABG_Tile* Tile, const FIntPoint& Coords) const;
	void      GetNeighborCoords(const FIntPoint& Coords, TArray<FIntPoint>& OutNeighbors) const;
	bool      IsValidCoord(const FIntPoint& Coords) const;
	bool      IsEdgeTile(const FIntPoint& Coords) const;
};
