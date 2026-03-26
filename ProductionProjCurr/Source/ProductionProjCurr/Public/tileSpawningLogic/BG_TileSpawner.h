// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Noise/FastNoiseLite.h"
#include "BG_TileSpawner.generated.h"

// Forward declarations
class ABG_Tile;
class ATileManager;
class UStaticMeshComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGridBuilt);

// Delegate declaration for when tiles are spawned

UENUM(BlueprintType)
enum class EBiomeType : uint8
{
	Water,
	Grassland,
	Hill
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

	void BuildGrid();

	UPROPERTY(BlueprintAssignable, Category = "Tile Spawner")
	FOnGridBuilt OnGridBuilt;




private:
	// Grid Setup
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Setup", meta = (AllowPrivateAccess = "true"))
	float tileWidth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Setup", meta = (AllowPrivateAccess = "true"))
	int32 numberOfColumns;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Setup", meta = (AllowPrivateAccess = "true"))
	int32 numberOfRows;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Setup", meta = (AllowPrivateAccess = "true"))
	float xSpawnOffset;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Setup", meta = (AllowPrivateAccess = "true"))
	float ySpawnOffset;

	// Noise Settings
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Setup", meta = (AllowPrivateAccess = "true"))
	float noiseFrequency;

	// Tile Classes
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hex | Biomes", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABG_Tile> TileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Biomes", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<ABG_Tile>> WaterTiles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Biomes", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABG_Tile> HillTile;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Biomes", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<ABG_Tile>> MeadowTiles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Biomes", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABG_Tile> PathTile;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Biomes", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABG_Tile> MeadowDefaultTile;

	TArray<TArray<ABG_Tile*>> TileGrid;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TileManager", meta = (AllowPrivateAccess = "true"))
	ATileManager* TileManager;


	FRandomStream randomStream;

	// Methods
	void spawnGrid(const float& randomNum);
	void clearGrid();

	TSubclassOf<ABG_Tile> GetTileClassForBiome(EBiomeType Biome) const;
	EBiomeType			  generateBiomeTypeBasedOnNoise(int32 rows, int32 cols, FastNoiseLite& _Noise);
	ABG_Tile*			  spawnTile(TSubclassOf<ABG_Tile> _ChosenTileClass, const FTransform& _instanceTransform);
	TSubclassOf<ABG_Tile> PickVariantFromNoise(
		const TArray<TSubclassOf<ABG_Tile>>& Variants,
		FastNoiseLite&						 Noise,
		int32								 Col,
		int32								 Row);



	bool IsEdgeTile(const FIntPoint& Coords) const;

	void SpawnPath();


	bool TryBuildRandomPath(TArray<FIntPoint>& OutPath);
	void GetNeighborCoords(const FIntPoint& Coords, TArray<FIntPoint>& OutNeighbors) const;
	bool IsValidCoord(const FIntPoint& Coords) const;

	int32 GetEdgeMask(const FIntPoint& Coords) const;
	bool IsDifferentEdge(const FIntPoint& Start, const FIntPoint& Current) const;

	void ChangeTileToPath(const FIntPoint& Coords);


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Path", meta = (AllowPrivateAccess = "true"))
	int32 numberOfPaths = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Path", meta = (AllowPrivateAccess = "true"))
	int32 minPathDistance = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Path", meta = (AllowPrivateAccess = "true"))
	float turnChance = 0.25f;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Setup", meta = (AllowPrivateAccess = "true"))
	float centerBiasStrength = 0.35f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Setup", meta = (AllowPrivateAccess = "true"))
	float centerBiasExponent = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hex | Foliage", meta = (AllowPrivateAccess = "true"))
	float foliageSpawnChance = 0.6f;

public:
	int getNumberOfCols() { return numberOfColumns; }
	int getNumberOfRows() { return numberOfRows; }
};

