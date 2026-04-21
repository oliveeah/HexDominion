// Fill out your copyright notice in the Description page of Project Settings.

#include "tileSpawningLogic/BG_TileSpawner.h"
#include "tileSpawningLogic/BG_Tile.h"
#include "tileSpawningLogic/TileManager.h"
#include "tileSpawningLogic/TileSpawner_Data.h"
#include "tileSpawningLogic/Tile_PathLogic.h"
#include "Kismet/GameplayStatics.h"

ABG_TileSpawner::ABG_TileSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABG_TileSpawner::BeginPlay()
{
	Super::BeginPlay();
}

void ABG_TileSpawner::BuildGrid()
{
	if (!TileManager)
	{
		TileManager = Cast<ATileManager>(UGameplayStatics::GetActorOfClass(this, ATileManager::StaticClass()));
	}
	if (!TileSpawnerData)
	{
		UE_LOG(LogTemp, Warning, TEXT("TileSpawnerData not set; aborting BuildGrid."));
		return;
	}

	const float randomNum = FMath::Rand();
	randomStream.Initialize(randomNum);

	clearGrid();
	spawnGrid(randomNum);

	PathLogic = NewObject<UTile_PathLogic>(this);
	PathLogic->Initialize(&TileGrid, TileSpawnerData, TileManager, &randomStream, GetWorld(), this);
	PathLogic->SpawnPaths();
	PathLogic->PlacePlayerSpawnTeleporters();

	if (TileGrid.Num() > 0)
	{
		OnGridBuilt.Broadcast();
	}
}

void ABG_TileSpawner::clearGrid()
{
	for (TArray<ABG_Tile*>& Row : TileGrid)
	{
		for (ABG_Tile* Tile : Row)
		{
			if (Tile && !Tile->IsPendingKillPending())
			{
				Tile->Destroy();
			}
		}
	}
	TileGrid.Empty();
}

void ABG_TileSpawner::spawnGrid(const float& randomNum)
{
	if (!GetWorld() || !TileSpawnerData)
		return;

	const UTileSpawner_Data& Data = *TileSpawnerData;
	const float hexWidth = Data.tileWidth;
	const float hexHeight = hexWidth * 0.866f;
	const FVector tileSpawnerLocation = GetActorLocation();

	FastNoiseLite Noise;
	Noise.SetSeed(static_cast<int>(randomNum));
	Noise.SetNoiseType(FastNoiseLite::NoiseType_ValueCubic);
	Noise.SetFrequency(Data.noiseFrequency);

	TileGrid.SetNum(Data.numberOfRows);

	if (TileManager)
	{
		TileManager->SetGridWidth(Data.numberOfColumns);
		TileManager->SetGridHeight(Data.numberOfRows);
	}

	for (int rows = 0; rows < Data.numberOfRows; ++rows)
	{
		TileGrid[rows].SetNum(Data.numberOfColumns);

		for (int cols = 0; cols < Data.numberOfColumns; ++cols)
		{
			const EBiomeType biomeType = generateBiomeTypeBasedOnNoise(rows, cols, Noise);
			TSubclassOf<ABG_Tile> ChosenTileClass = GetTileClassForBiome(biomeType);

			// Apply foliage/special tiles only to grassland
			if (biomeType == EBiomeType::Grassland)
			{
				if (Data.ObeliskTile && randomStream.FRand() < Data.obeliskSpawnChance)
				{
					ChosenTileClass = Data.ObeliskTile;
				}
				else if (Data.MeadowTiles.Num() > 0 && randomStream.FRand() < Data.foliageSpawnChance)
				{
					ChosenTileClass = PickVariantFromNoise(Data.MeadowTiles, Noise, cols, rows);
				}
			}

			// Calculate position
			const float xOffset = (rows % 2 == 0) ? 0.0f : (hexWidth * 0.5f);
			float Nx = cols + (rows % 2) * 0.5f;
			float Ny = rows * 0.8660254f;
			float HeightNoise = Noise.GetNoise(Nx, Ny);
			float Height = HeightNoise * Data.ySpawnOffset;

			// Only hills have height variation
			if (biomeType == EBiomeType::Hill)
			{
				Height = FMath::Abs(Height);
			}
			else
			{
				Height = 0.0f;
			}

			FVector spawnLocation = tileSpawnerLocation + FVector(cols * hexWidth + xOffset, rows * hexHeight, Height);
			const FTransform instanceTransform(FRotator::ZeroRotator, spawnLocation);

			ABG_Tile* NewTile = spawnTile(ChosenTileClass, instanceTransform);
			if (NewTile)
			{
				TileGrid[rows][cols] = NewTile;
				NewTile->SetGridCoordinates(FIntPoint(cols, rows));
				NewTile->ApplyHueFromNoise(HeightNoise);

				if (TileManager)
				{
					NewTile->OnTileSelectedDelegate.AddDynamic(TileManager, &ATileManager::OnTileClicked);
					TileManager->RegisterTile(FIntPoint(cols, rows), NewTile);
				}
			}
		}
	}
}

TSubclassOf<ABG_Tile> ABG_TileSpawner::GetTileClassForBiome(EBiomeType Biome) const
{
	switch (Biome)
	{
		case EBiomeType::Grassland:
			return TileSpawnerData->MeadowDefaultTile ? TileSpawnerData->MeadowDefaultTile : TileSpawnerData->TileClass;
		case EBiomeType::Hill:
			return TileSpawnerData->HillTile;
		default:
			return TileSpawnerData->TileClass;
	}
}

EBiomeType ABG_TileSpawner::generateBiomeTypeBasedOnNoise(int32 rows, int32 cols, FastNoiseLite& _Noise)
{
	float Nx = cols + (rows % 2) * 0.5f;
	float Ny = rows * 0.8660254f;
	float Value = (_Noise.GetNoise(Nx, Ny) + 1.f) * 0.5f;

	// Apply center bias
	const FVector2D Center((TileSpawnerData->numberOfColumns - 1) * 0.5f, (TileSpawnerData->numberOfRows - 1) * 0.5f);
	const FVector2D Pos(cols, rows);
	const float MaxRadius = FMath::Max(Center.X, Center.Y);
	const float Dist = FVector2D::Distance(Pos, Center);
	const float T = 1.0f - FMath::Clamp(Dist / MaxRadius, 0.0f, 1.0f);
	const float CenterWeight = FMath::Pow(T, TileSpawnerData->centerBiasExponent);

	Value = FMath::Clamp(
		FMath::Lerp(Value, 1.0f, TileSpawnerData->centerBiasStrength * CenterWeight),
		0.0f, 1.0f);

	if (Value < TileSpawnerData->grasslandThreshold)
		return EBiomeType::Grassland;
	return EBiomeType::Hill;
}

ABG_Tile* ABG_TileSpawner::spawnTile(TSubclassOf<ABG_Tile> _ChosenTileClass, const FTransform& _instanceTransform)
{
	if (!_ChosenTileClass || !GetWorld())
		return nullptr;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	return GetWorld()->SpawnActor<ABG_Tile>(_ChosenTileClass, _instanceTransform, SpawnParams);
}

TSubclassOf<ABG_Tile> ABG_TileSpawner::PickVariantFromNoise(
	const TArray<TSubclassOf<ABG_Tile>>& Variants,
	FastNoiseLite& Noise,
	int32 Col,
	int32 Row)
{
	if (Variants.Num() == 0)
		return nullptr;

	const int32 Index = randomStream.RandRange(0, Variants.Num() - 1);
	return Variants[Index];
}

// ============================================================================
// PATH GENERATION (Just normal paths, not teleporters)
// ============================================================================


int ABG_TileSpawner::getNumberOfCols()
{
	return TileSpawnerData ? TileSpawnerData->numberOfColumns : 0;
}

int ABG_TileSpawner::getNumberOfRows()
{
	return TileSpawnerData ? TileSpawnerData->numberOfRows : 0;
}
