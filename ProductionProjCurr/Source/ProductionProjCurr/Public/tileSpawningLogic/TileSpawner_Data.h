// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TileSpawner_Data.generated.h"

class ABG_Tile;

UCLASS(BlueprintType)
class PRODUCTIONPROJCURR_API UTileSpawner_Data : public UDataAsset
{
	GENERATED_BODY()

public:
	// Grid Setup
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Parameters | Setup")
	float tileWidth = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Parameters | Setup")
	int32 numberOfColumns = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Parameters | Setup")
	int32 numberOfRows = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Parameters | Setup")
	float xSpawnOffset = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Parameters | Setup")
	float ySpawnOffset = 0.0f;

	// Noise Settings
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Parameters | Noise")
	float noiseFrequency = 0.0f;

	// Tile Classes
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Tiles | Biomes")
	TSubclassOf<ABG_Tile> TileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Tiles | Biomes")
	TArray<TSubclassOf<ABG_Tile>> WaterTiles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Tiles | Biomes")
	TSubclassOf<ABG_Tile> HillTile;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Tiles | Biomes")
	TArray<TSubclassOf<ABG_Tile>> MeadowTiles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Tiles | Biomes")
	TSubclassOf<ABG_Tile> PathTile;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Tiles | Biomes")
	TSubclassOf<ABG_Tile> MeadowDefaultTile;

	// Path Settings
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Parameters | Path")
	int32 numberOfPaths = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Parameters | Path")
	int32 minPathDistance = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Parameters | Path")
	float turnChance = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Parameters | Path")
	bool bUseSubdivisionGaps = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Parameters | Path")
	int32 subdivisionGapWidth = 1;

	// Bias + Foliage
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Parameters | Setup")
	float centerBiasStrength = 0.35f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Parameters | Setup")
	float centerBiasExponent = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Parameters | Foliage")
	float foliageSpawnChance = 0.6f;

	// Biome Thresholds
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Parameters | Biomes")
	float waterThreshold = 0.4f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Parameters | Biomes")
	float grasslandThreshold = 0.7f;

	// Special Tiles
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Tiles | Special")
	TSubclassOf<ABG_Tile> TeleporterTile;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Parameters | Special")
	float teleporterSpawnChance = 0.05f;

	// Obelisk Tiles
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Tiles | Special")
	TSubclassOf<ABG_Tile> ObeliskTile;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Parameters | Special")
	float obeliskSpawnChance = 0.05f;
};