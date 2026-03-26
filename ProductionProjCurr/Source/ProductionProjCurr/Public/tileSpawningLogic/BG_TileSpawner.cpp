// Fill out your copyright notice in the Description page of Project Settings.

#include "BG_TileSpawner.h"
#include "BG_Tile.h"
#include "TileManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABG_TileSpawner::ABG_TileSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
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
	if (!TileManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("TileManager not found; aborting BuildGrid."));
		return;
	}

	// Generate random number and seed with it
	const float randomNum = FMath::Rand();
	randomStream.Initialize(randomNum);

	// Clear old instances so we don't duplicate
	clearGrid();

	// Spawn new tiles
	spawnGrid(randomNum);

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
	if (!GetWorld())
		return;

	const float	  hexWidth = tileWidth;
	const float	  hexHeight = hexWidth * 0.866f; // hexHeight
	const FVector tileSpawnerLocation = GetActorLocation();

	FastNoiseLite Noise;
	Noise.SetSeed(randomNum);
	Noise.SetNoiseType(FastNoiseLite::NoiseType_ValueCubic);
	Noise.SetFrequency(noiseFrequency);

	TileGrid.SetNum(numberOfRows);

	if (TileManager)
	{
		TileManager->SetGridWidth(numberOfColumns);
		TileManager->SetGridHeight(numberOfRows);
	}
		
	for (int32 rows = 0; rows < numberOfRows; ++rows)
	{
		TileGrid[rows].SetNum(numberOfColumns);
		for (int32 cols = 0; cols < numberOfColumns; ++cols)
		{

			// Determine biome type based on noise
			const EBiomeType biomeType = generateBiomeTypeBasedOnNoise(rows, cols, Noise);

			// Get tile class for biome
			TSubclassOf<ABG_Tile> ChosenTileClass = GetTileClassForBiome(biomeType);

			if (biomeType == EBiomeType::Grassland && MeadowTiles.Num() > 0)
			{
				ChosenTileClass = PickVariantFromNoise(MeadowTiles, Noise, cols, rows);
			}
			else if (biomeType == EBiomeType::Water && WaterTiles.Num() > 0)
			{
				ChosenTileClass = PickVariantFromNoise(WaterTiles, Noise, cols, rows);
			}

			// Offset every other row
			const float xOffset = (rows % 2 == 0) ? 0.0f : (hexWidth * 0.5f);
			float		Nx = cols + (rows % 2) * 0.5f;
			float		Ny = rows * 0.8660254f;

			float HeightNoise = Noise.GetNoise(Nx, Ny); // reuse same coords

		float Height = HeightNoise * ySpawnOffset;

			switch (biomeType)
			{
				case EBiomeType::Water:
					Height = -FMath::Abs(Height);
					break;
				case EBiomeType::Hill:
					Height = FMath::Abs(Height);
					break;
				default:
					Height = 0.0f;
					break;
			}

			FVector spawnLocation = tileSpawnerLocation + FVector(cols * hexWidth + xOffset, rows * hexHeight, Height);

			const FTransform instanceTransform(FRotator::ZeroRotator, spawnLocation);

			// Spawn the tile
			ABG_Tile* NewTile = spawnTile(ChosenTileClass, instanceTransform);

			if (NewTile) // set grid coords, register with manager and bind delegate
			{
				TileGrid[rows][cols] = NewTile;
				NewTile->gridCoordinates = FIntPoint(cols, rows);

				if (biomeType == EBiomeType::Grassland)
				{
					ChosenTileClass = PickVariantFromNoise(MeadowTiles, Noise, cols, rows);
				}

				if (TileManager)
				{
					NewTile->OnTileSelectedDelegate.AddDynamic(TileManager, &ATileManager::OnTileClicked);
					TileManager->RegisterTile(FIntPoint(cols, rows), NewTile);
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("TileManager not set in TileSpawner! Cannot bind delegate."));
				}
			}
		}
	}

	SpawnPath();


}

TSubclassOf<ABG_Tile> ABG_TileSpawner::GetTileClassForBiome(EBiomeType Biome) const
{
	switch (Biome)
	{
		case EBiomeType::Water:
			return WaterTiles.Num() > 0 ? WaterTiles[0] : TileClass;
		case EBiomeType::Grassland:
			return MeadowTiles.Num() > 0 ? MeadowTiles[0] : TileClass;
		case EBiomeType::Hill:
			return HillTile;
		default:
			return TileClass; // Fallback to base tile
	}
}

EBiomeType ABG_TileSpawner::generateBiomeTypeBasedOnNoise(int32 rows, int32 cols, FastNoiseLite& _Noise)
{
	float Nx = cols + (rows % 2) * 0.5f;
	float Ny = rows * 0.8660254f;

	float Value = (_Noise.GetNoise(Nx, Ny) + 1.f) * 0.5f;

	const FVector2D Center((numberOfColumns - 1) * 0.5f, (numberOfRows - 1) * 0.5f);
	const FVector2D Pos(cols, rows);
	const float		MaxRadius = FMath::Max(Center.X, Center.Y);
	const float		Dist = FVector2D::Distance(Pos, Center);
	const float		T = 1.0f - FMath::Clamp(Dist / MaxRadius, 0.0f, 1.0f);
	const float		CenterWeight = FMath::Pow(T, centerBiasExponent);

	Value = FMath::Clamp(
		FMath::Lerp(Value, 1.0f, centerBiasStrength * CenterWeight),
		0.0f, 1.0f);

	if (Value < 0.4f)
		return EBiomeType::Water;
	if (Value < 0.7f)
		return EBiomeType::Grassland;
	return EBiomeType::Hill;

}

ABG_Tile* ABG_TileSpawner::spawnTile(TSubclassOf<ABG_Tile> _ChosenTileClass, const FTransform& _instanceTransform)
{
	if (!_ChosenTileClass)
		return nullptr;

	UWorld* World = GetWorld();
	if (!World)
		return nullptr;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	ABG_Tile* NewTile = World->SpawnActor<ABG_Tile>(_ChosenTileClass, _instanceTransform, SpawnParams);

	return NewTile;
}

TSubclassOf<ABG_Tile> ABG_TileSpawner::PickVariantFromNoise(
	const TArray<TSubclassOf<ABG_Tile>>& Variants,
	FastNoiseLite&						 Noise,
	int32								 Col,
	int32								 Row)
{
	if (Variants.Num() == 0)
		return nullptr;

	const int32 Index = randomStream.RandRange(0, Variants.Num() - 1);

	return Variants[Index];
}

bool ABG_TileSpawner::IsEdgeTile(const FIntPoint& Coords) const
{
	return Coords.X == 0 || Coords.Y == 0 || Coords.X == numberOfColumns - 1 || Coords.Y == numberOfRows - 1;
}

bool ABG_TileSpawner::IsValidCoord(const FIntPoint& Coords) const
{
	return TileGrid.IsValidIndex(Coords.Y) && TileGrid[Coords.Y].IsValidIndex(Coords.X);
}

void ABG_TileSpawner::GetNeighborCoords(const FIntPoint& Coords, TArray<FIntPoint>& OutNeighbors) const
{
	OutNeighbors.Reset();

	static const FIntPoint EvenRowDirs[6] = {
		{ -1, 0 }, { 1, 0 },
		{ -1, -1 }, { 0, -1 },
		{ -1, 1 }, { 0, 1 }
	};

	static const FIntPoint OddRowDirs[6] = {
		{ -1, 0 }, { 1, 0 },
		{ 0, -1 }, { 1, -1 },
		{ 0, 1 }, { 1, 1 }
	};

	const FIntPoint* Directions = (Coords.Y % 2 == 0) ? EvenRowDirs : OddRowDirs;

	for (int32 i = 0; i < 6; ++i)
	{
		const FIntPoint Neighbor = Coords + Directions[i];
		if (IsValidCoord(Neighbor))
		{
			OutNeighbors.Add(Neighbor);
		}
	}
}

int32 ABG_TileSpawner::GetEdgeMask(const FIntPoint& Coords) const
{
	int32 Mask = 0;
	if (Coords.X == 0)					 Mask |= 1; // left
	if (Coords.X == numberOfColumns - 1) Mask |= 2; // right
	if (Coords.Y == 0)					 Mask |= 4; // top
	if (Coords.Y == numberOfRows - 1)	 Mask |= 8; // bottom
	return Mask;
}

bool ABG_TileSpawner::IsDifferentEdge(const FIntPoint& Start, const FIntPoint& Current) const
{
	const int32 StartMask = GetEdgeMask(Start);
	const int32 CurrentMask = GetEdgeMask(Current);
	return (CurrentMask & StartMask) == 0;
}

void ABG_TileSpawner::ChangeTileToPath(const FIntPoint& Coords)
{
	ABG_Tile* OldTile = TileGrid[Coords.Y][Coords.X];
	if (!OldTile)
		return;

	const FVector	 ActorScale = OldTile->GetActorScale3D();
	const FVector	 MeshScale = OldTile->tileMesh ? OldTile->tileMesh->GetRelativeScale3D() : FVector::OneVector;
	const FVector	 RootRelLoc = OldTile->GetRootComponent() ? OldTile->GetRootComponent()->GetRelativeLocation() : FVector::ZeroVector;
	const FRotator	 RootRelRot = OldTile->GetRootComponent() ? OldTile->GetRootComponent()->GetRelativeRotation() : FRotator::ZeroRotator;
	const FTransform TileTransform = OldTile->GetActorTransform();

	OldTile->Destroy();

	ABG_Tile* NewTile = spawnTile(PathTile, TileTransform);
	if (!NewTile)
		return;

	NewTile->SetActorScale3D(ActorScale);
	if (NewTile->tileMesh)
	{
		NewTile->tileMesh->SetRelativeScale3D(MeshScale);
	}
	if (NewTile->GetRootComponent())
	{
		NewTile->GetRootComponent()->SetRelativeLocation(RootRelLoc);
		NewTile->GetRootComponent()->SetRelativeRotation(RootRelRot);
	}

	NewTile->gridCoordinates = Coords;
	TileGrid[Coords.Y][Coords.X] = NewTile;

	if (TileManager)
	{
		NewTile->OnTileSelectedDelegate.AddDynamic(TileManager, &ATileManager::OnTileClicked);
		TileManager->RegisterTile(Coords, NewTile);
	}
}


bool ABG_TileSpawner::TryBuildRandomPath(TArray<FIntPoint>& OutPath)
{
	OutPath.Reset();

	const int32 MaxStartAttempts = numberOfRows * numberOfColumns * 2;
	int32 StartAttempts = 0;
	FIntPoint Start(-1, -1);

	while (++StartAttempts < MaxStartAttempts) // loop until we find a valid starting edge tile or exhaust attempts
	{
		const int32 RandomCol = randomStream.RandRange(0, numberOfColumns - 1);
		const int32 RandomRow = randomStream.RandRange(0, numberOfRows - 1);
		const FIntPoint Candidate(RandomCol, RandomRow);

		if (IsEdgeTile(Candidate) && IsValidCoord(Candidate) && TileGrid[RandomRow][RandomCol])
		{
			Start = Candidate;
			break;
		}
	}

	if (!IsValidCoord(Start)) // Failed to find a valid starting edge tile
		return false;

	TSet<FIntPoint> Visited;
	Visited.Add(Start);
	OutPath.Add(Start);

	FIntPoint Current = Start;
	FIntPoint Previous = Start;
	const int32 MaxSteps = numberOfRows * numberOfColumns * 2;

	for (int32 Step = 0; Step < MaxSteps; ++Step)
	{
		const int32 DistanceFromStart = FMath::Abs(Current.X - Start.X) + FMath::Abs(Current.Y - Start.Y); // Manhattan distance
		if (Step > 0 && IsEdgeTile(Current) && IsDifferentEdge(Start, Current) && DistanceFromStart >= minPathDistance)
		{
			return true;
		}

		TArray<FIntPoint> Neighbors;
		GetNeighborCoords(Current, Neighbors);

		TArray<FIntPoint> Unvisited;
		for (const FIntPoint& N : Neighbors)
		{
			if (!Visited.Contains(N))
			{
				Unvisited.Add(N);
			}
		}

		if (Unvisited.Num() == 0)
		{
			return false; // dead-end, no backtracking
		}

		// Prefer moves that increase distance from the start
		TArray<FIntPoint> Outward;
		for (const FIntPoint& N : Unvisited)
		{
			const int32 NextDistance = FMath::Abs(N.X - Start.X) + FMath::Abs(N.Y - Start.Y);
			if (NextDistance >= DistanceFromStart)
			{
				Outward.Add(N);
			}
		}

		TArray<FIntPoint> Choices = Outward.Num() > 0 ? Outward : Unvisited;

		// Prefer to go straight, but sometimes turn for natural variation
		FIntPoint Forward = Current + (Current - Previous);
		int32 ForwardIndex = Choices.IndexOfByKey(Forward);

		const bool bForceTurn = randomStream.FRand() < turnChance || ForwardIndex == INDEX_NONE;

		FIntPoint Next = Forward;
		if (bForceTurn)
		{
			Next = Choices[randomStream.RandRange(0, Choices.Num() - 1)];
		}
		else
		{
			Next = Choices[ForwardIndex];
		}

		Previous = Current;
		Current = Next;

		Visited.Add(Current);
		OutPath.Add(Current);
	}

	return false;
}

void ABG_TileSpawner::SpawnPath()
{
	if (TileGrid.Num() == 0 || numberOfRows <= 0 || numberOfColumns <= 0 || !PathTile)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnPath failed: grid is not initialized, or pathtile class not set."));
		return;
	}

	const int32 PathsToGenerate = FMath::Max(1, numberOfPaths);
	const int32 MaxPathAttempts = 10;

	for (int32 PathIndex = 0; PathIndex < PathsToGenerate; ++PathIndex) // for each path we want to generate
	{
		TArray<FIntPoint> Path;
		bool bBuilt = false;

		for (int32 Attempt = 0; Attempt < MaxPathAttempts; ++Attempt) // for each attempt to build a path
		{
			if (TryBuildRandomPath(Path))
			{
				bBuilt = true;
				break;
			}
		}

		if (!bBuilt)
		{
			UE_LOG(LogTemp, Warning, TEXT("SpawnPath failed: could not reach another edge."));
			continue;
		}

		for (const FIntPoint& Coords : Path) // for each tile in the successful path
		{
			if (!IsValidCoord(Coords))
				continue;

			ChangeTileToPath(Coords);

		}
	}
}
