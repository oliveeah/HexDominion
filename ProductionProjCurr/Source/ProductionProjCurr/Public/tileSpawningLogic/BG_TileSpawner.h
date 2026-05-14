#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Noise/FastNoiseLite.h"
#include "BG_TileSpawner.generated.h"

class ABG_Tile;
class ATileManager;
class UTileSpawner_Data;
class UTile_PathLogic;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGridBuilt);

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

	const TArray<TArray<ABG_Tile*>>& getTileGrid() const { return TileGrid; }

	void BuildGrid();

	UPROPERTY(BlueprintAssignable, Category = "Tile Spawner")
	FOnGridBuilt OnGridBuilt;

	int getNumberOfCols();
	int getNumberOfRows();

	UTileSpawner_Data* GetTileSpawnerData() const { return TileSpawnerData; }

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tile Spawner", meta = (AllowPrivateAccess = "true"))
	UTileSpawner_Data* TileSpawnerData;

	TArray<TArray<ABG_Tile*>> TileGrid;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TileManager", meta = (AllowPrivateAccess = "true"))
	ATileManager* TileManager;

	UPROPERTY()
	UTile_PathLogic* PathLogic;

	FRandomStream randomStream;

	void spawnGrid(const float& randomNum);
	void clearGrid();
	ABG_Tile* spawnTile(TSubclassOf<ABG_Tile> _ChosenTileClass, const FTransform& _instanceTransform);

	TSubclassOf<ABG_Tile> GetTileClassForBiome(EBiomeType Biome) const;
	EBiomeType generateBiomeTypeBasedOnNoise(int32 rows, int32 cols, FastNoiseLite& _Noise);
	TSubclassOf<ABG_Tile> PickVariantFromNoise(
		const TArray<TSubclassOf<ABG_Tile>>& Variants,
		FastNoiseLite& Noise,
		int32 Col,
		int32 Row);
};
