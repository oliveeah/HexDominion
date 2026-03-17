// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Noise/FastNoiseLite.h"
#include "BG_TileSpawner.generated.h"

// Forward declarations
class ABG_Tile;
class ATileManager;

// Delegate declaration for when tiles are spawned

UENUM(BlueprintType)
enum class EBiomeType : uint8
{
	Water,
	Sandy,
	Grassland,
	Forest,
	Stone,
	Hill,
	Mountain
};

UCLASS()
class PRODUCTIONPROJCURR_API ABG_TileSpawner : public AActor
{
public:
	GENERATED_BODY()

	ABG_TileSpawner();

	virtual void BeginPlay() override;


	const TArray<TArray<ABG_Tile*>>& getTileGrid() const
	{
		return TileGrid;
	}

protected:
	// Grid Setup
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex | Setup")
	float tileWidth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex | Setup")
	int32 numberOfColumns;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex | Setup")
	int32 numberOfRows;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex | Setup")
	float xSpawnOffset;

	// Noise Settings
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Setup")
	float noiseFrequency;

	// Tile Classes
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hex | Biomes")
	TSubclassOf<ABG_Tile> TileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex | Biomes")
	TSubclassOf<ABG_Tile> WaterTile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex | Biomes")
	TSubclassOf<ABG_Tile> SandyTile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex | Biomes")
	TArray<TSubclassOf<ABG_Tile>> MeadowTiles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex | Biomes")
	TArray<TSubclassOf<ABG_Tile>> ForestTiles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex | Biomes")
	TArray<TSubclassOf<ABG_Tile>> StoneTiles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex | Biomes")
	TArray<TSubclassOf<ABG_Tile>> RockHillTiles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hex | Biomes")
	TSubclassOf<ABG_Tile> MountainTile;

	TArray<TArray<ABG_Tile*>> TileGrid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileManager")
	ATileManager* TileManager;

	FRandomStream randomStream;

	// Methods
	void spawnGrid(const float& randomNum);
	void clearGrid();

	TSubclassOf<ABG_Tile> GetTileClassForBiome(EBiomeType Biome) const;
	EBiomeType generateBiomeTypeBasedOnNoise(int32 rows, int32 cols, FastNoiseLite _Noise);
	ABG_Tile* spawnTile(TSubclassOf<ABG_Tile> _ChosenTileClass, const FTransform& _instanceTransform);
	TSubclassOf<ABG_Tile> PickVariantFromNoise(
		const TArray<TSubclassOf<ABG_Tile>>& Variants,
		FastNoiseLite&						 Noise,
		int32								 Col,
		int32								 Row);
};