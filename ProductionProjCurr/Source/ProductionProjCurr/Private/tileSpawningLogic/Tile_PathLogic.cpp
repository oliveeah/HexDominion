// Fill out your copyright notice in the Description page of Project Settings.

#include "tileSpawningLogic/Tile_PathLogic.h"
#include "tileSpawningLogic/BG_Tile.h"
#include "tileSpawningLogic/TileManager.h"
#include "tileSpawningLogic/TileSpawner_Data.h"

void UTile_PathLogic::Initialize(
	TArray<TArray<ABG_Tile*>>* InTileGrid,
	UTileSpawner_Data*          InData,
	ATileManager*               InTileManager,
	FRandomStream*              InRandomStream,
	UWorld*                     InWorld,
	AActor*                     InOwner)
{
	TileGrid        = InTileGrid;
	TileSpawnerData = InData;
	TileManager     = InTileManager;
	RandomStream    = InRandomStream;
	World           = InWorld;
	Owner           = InOwner;
}

// ============================================================================
// PATH GENERATION
// ============================================================================

void UTile_PathLogic::SpawnPaths()
{
	if (!TileGrid || TileGrid->Num() == 0 || !TileSpawnerData || !TileSpawnerData->PathTile)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnPaths failed: grid not initialized or PathTile not set."));
		return;
	}

	const int32 PathsToGenerate = FMath::Max<int32>(1, TileSpawnerData->numberOfPaths);
	const int32 MaxPathAttempts = 10;

	for (int32 PathIndex = 0; PathIndex < PathsToGenerate; ++PathIndex)
	{
		TArray<FIntPoint> Path;
		bool bBuilt = false;

		for (int32 Attempt = 0; Attempt < MaxPathAttempts; ++Attempt)
		{
			if (TryBuildRandomPath(Path))
			{
				bBuilt = true;
				break;
			}
		}

		if (!bBuilt)
		{
			UE_LOG(LogTemp, Warning, TEXT("Path %d failed to build after %d attempts"), PathIndex, MaxPathAttempts);
			continue;
		}

		for (const FIntPoint& Coords : Path)
		{
			if (IsValidCoord(Coords))
			{
				ChangeTileToPath(Coords);
			}
		}

		UE_LOG(LogTemp, Display, TEXT("Successfully built path %d with %d tiles"), PathIndex, Path.Num());
	}
}

bool UTile_PathLogic::TryBuildRandomPath(TArray<FIntPoint>& OutPath)
{
	OutPath.Reset();

	const int32 MaxStartAttempts = TileSpawnerData->numberOfRows * TileSpawnerData->numberOfColumns * 2;
	FIntPoint Start(-1, -1);

	for (int32 Attempt = 0; Attempt < MaxStartAttempts; ++Attempt)
	{
		const int32 RandomCol = RandomStream->RandRange(0, TileSpawnerData->numberOfColumns - 1);
		const int32 RandomRow = RandomStream->RandRange(0, TileSpawnerData->numberOfRows - 1);
		const FIntPoint Candidate(RandomCol, RandomRow);

		if (!IsEdgeTile(Candidate) && IsValidCoord(Candidate))
		{
			ABG_Tile* Tile = (*TileGrid)[RandomRow][RandomCol];
			if (Tile && !Tile->getIsSpecialTile())
			{
				Start = Candidate;
				break;
			}
		}
	}

	if (!IsValidCoord(Start))
		return false;

	TSet<FIntPoint> Visited;
	Visited.Add(Start);
	OutPath.Add(Start);

	FIntPoint Current = Start;
	const int32 MaxSteps = TileSpawnerData->numberOfRows * TileSpawnerData->numberOfColumns;

	for (int32 Step = 0; Step < MaxSteps; ++Step)
	{
		TArray<FIntPoint> Neighbors;
		GetNeighborCoords(Current, Neighbors);

		TArray<FIntPoint> SafeUnvisited;
		for (const FIntPoint& N : Neighbors)
		{
			if (Visited.Contains(N) || !IsValidCoord(N))
				continue;

			ABG_Tile* NeighborTile = (*TileGrid)[N.Y][N.X];
			if (!NeighborTile || NeighborTile->getIsSpecialTile())
				continue;

			if (!WouldIsolateTile(N, Visited))
			{
				SafeUnvisited.Add(N);
			}
		}

		if (SafeUnvisited.Num() == 0)
			return false;

		FIntPoint Next = SafeUnvisited[RandomStream->RandRange(0, SafeUnvisited.Num() - 1)];
		Current = Next;

		Visited.Add(Current);
		OutPath.Add(Current);

		if (OutPath.Num() >= TileSpawnerData->minPathDistance)
			return true;
	}

	return OutPath.Num() >= TileSpawnerData->minPathDistance;
}

bool UTile_PathLogic::WouldIsolateTile(const FIntPoint& CandidatePathTile, const TSet<FIntPoint>& CurrentPathSet) const
{
	TArray<FIntPoint> CandidateNeighbors;
	GetNeighborCoords(CandidatePathTile, CandidateNeighbors);

	for (const FIntPoint& Neighbor : CandidateNeighbors)
	{
		if (CurrentPathSet.Contains(Neighbor) || !IsValidCoord(Neighbor))
			continue;

		ABG_Tile* NeighborTile = (*TileGrid)[Neighbor.Y][Neighbor.X];
		if (!NeighborTile || NeighborTile->getIsSpecialTile())
			continue;

		TArray<FIntPoint> NeighborOfNeighbor;
		GetNeighborCoords(Neighbor, NeighborOfNeighbor);

		int32 RemainingWalkable = 0;
		for (const FIntPoint& N2 : NeighborOfNeighbor)
		{
			if (N2 == CandidatePathTile || CurrentPathSet.Contains(N2) || !IsValidCoord(N2))
				continue;

			if ((*TileGrid)[N2.Y][N2.X])
				++RemainingWalkable;
		}

		if (RemainingWalkable == 0)
			return true;
	}

	return false;
}

void UTile_PathLogic::ChangeTileToPath(const FIntPoint& Coords)
{
	ABG_Tile* OldTile = (*TileGrid)[Coords.Y][Coords.X];
	if (!OldTile)
		return;

	const FVector ActorScale  = OldTile->GetActorScale3D();
	const FVector MeshScale   = OldTile->tileMesh ? OldTile->tileMesh->GetRelativeScale3D() : FVector::OneVector;
	const FTransform Transform = OldTile->GetActorTransform();

	OldTile->Destroy();

	ABG_Tile* NewTile = SpawnTile(TileSpawnerData->PathTile, Transform);
	if (!NewTile)
		return;

	NewTile->SetActorScale3D(ActorScale);
	if (NewTile->tileMesh)
		NewTile->tileMesh->SetRelativeScale3D(MeshScale);

	NewTile->SetGridCoordinates(Coords);
	ApplyNoiseHue(NewTile, Coords);
	(*TileGrid)[Coords.Y][Coords.X] = NewTile;

	if (TileManager)
	{
		NewTile->OnTileSelectedDelegate.AddDynamic(TileManager, &ATileManager::OnTileClicked);
		TileManager->RegisterTile(Coords, NewTile);
	}
}

// ============================================================================
// TELEPORTER PLACEMENT
// ============================================================================

void UTile_PathLogic::PlacePlayerSpawnTeleporters()
{
	if (!TileSpawnerData || !TileSpawnerData->TeleporterTile)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot place teleporters: TeleporterTile not set"));
		return;
	}

	const int32 EdgeBuffer = 2;
	TArray<FIntPoint> PlayerSpawns;
	PlayerSpawns.Add(FIntPoint(EdgeBuffer, EdgeBuffer));
	PlayerSpawns.Add(FIntPoint(TileSpawnerData->numberOfColumns - EdgeBuffer - 1, EdgeBuffer));
	PlayerSpawns.Add(FIntPoint(EdgeBuffer, TileSpawnerData->numberOfRows - EdgeBuffer - 1));
	PlayerSpawns.Add(FIntPoint(TileSpawnerData->numberOfColumns - EdgeBuffer - 1, TileSpawnerData->numberOfRows - EdgeBuffer - 1));

	for (const FIntPoint& SpawnCoords : PlayerSpawns)
	{
		TArray<FIntPoint> Neighbors;
		GetNeighborCoords(SpawnCoords, Neighbors);

		for (const FIntPoint& NeighborCoords : Neighbors)
		{
			if (!IsValidCoord(NeighborCoords))
				continue;

			ABG_Tile* Tile = (*TileGrid)[NeighborCoords.Y][NeighborCoords.X];
			if (Tile && !Tile->getIsSpecialTile())
			{
				PlaceTeleporter(NeighborCoords);
				UE_LOG(LogTemp, Display, TEXT("Placed teleporter at (%d, %d) adjacent to spawn (%d, %d)"),
					NeighborCoords.X, NeighborCoords.Y, SpawnCoords.X, SpawnCoords.Y);
				break;
			}
		}
	}
}

void UTile_PathLogic::PlaceTeleporter(const FIntPoint& Coords)
{
	ABG_Tile* OldTile = (*TileGrid)[Coords.Y][Coords.X];
	if (!OldTile)
		return;

	const FVector ActorScale  = OldTile->GetActorScale3D();
	const FVector MeshScale   = OldTile->tileMesh ? OldTile->tileMesh->GetRelativeScale3D() : FVector::OneVector;
	const FTransform Transform = OldTile->GetActorTransform();

	OldTile->Destroy();

	ABG_Tile* NewTile = SpawnTile(TileSpawnerData->TeleporterTile, Transform);
	if (!NewTile)
		return;

	NewTile->SetActorScale3D(ActorScale);
	if (NewTile->tileMesh)
		NewTile->tileMesh->SetRelativeScale3D(MeshScale);

	NewTile->SetGridCoordinates(Coords);
	NewTile->SetIsSpecialTile(true);
	ApplyNoiseHue(NewTile, Coords);
	(*TileGrid)[Coords.Y][Coords.X] = NewTile;

	if (TileManager)
	{
		NewTile->OnTileSelectedDelegate.AddDynamic(TileManager, &ATileManager::OnTileClicked);
		TileManager->RegisterTile(Coords, NewTile);
		TileManager->RegisterTeleporterTile(Coords);
	}
}

// ============================================================================
// HELPERS
// ============================================================================

ABG_Tile* UTile_PathLogic::SpawnTile(TSubclassOf<ABG_Tile> TileClass, const FTransform& Transform)
{
	if (!TileClass || !World)
		return nullptr;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Owner;
	return World->SpawnActor<ABG_Tile>(TileClass, Transform, SpawnParams);
}

void UTile_PathLogic::ApplyNoiseHue(ABG_Tile* Tile, const FIntPoint& Coords) const
{
	if (!Tile || !TileSpawnerData)
		return;

	FastNoiseLite Noise;
	Noise.SetSeed(static_cast<int>(RandomStream->GetInitialSeed()));
	Noise.SetNoiseType(FastNoiseLite::NoiseType_ValueCubic);
	Noise.SetFrequency(TileSpawnerData->noiseFrequency);

	const float Nx = Coords.X + (Coords.Y % 2) * 0.5f;
	const float Ny = Coords.Y * 0.8660254f;
	Tile->ApplyHueFromNoise(Noise.GetNoise(Nx, Ny));
}

void UTile_PathLogic::GetNeighborCoords(const FIntPoint& Coords, TArray<FIntPoint>& OutNeighbors) const
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
			OutNeighbors.Add(Neighbor);
	}
}

bool UTile_PathLogic::IsValidCoord(const FIntPoint& Coords) const
{
	return TileGrid && TileGrid->IsValidIndex(Coords.Y) && (*TileGrid)[Coords.Y].IsValidIndex(Coords.X);
}

bool UTile_PathLogic::IsEdgeTile(const FIntPoint& Coords) const
{
	return Coords.X == 0 || Coords.Y == 0 ||
	       Coords.X == TileSpawnerData->numberOfColumns - 1 ||
	       Coords.Y == TileSpawnerData->numberOfRows - 1;
}
