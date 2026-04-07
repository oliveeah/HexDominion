// Fill out your copyright notice in the Description page of Project Settings.

#include "Occupant/TroopSpawner.h"
#include "tileSpawningLogic/BG_Tile.h"
#include "Occupant/Occupant_BaseClass.h"
#include "Occupant/Occupant_Troop_BaseClass.h"
#include "Occupant/Occupant_Building_BaseClass.h"
#include "gameMode/TurnManager.h"

ATroopSpawner::ATroopSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATroopSpawner::Initialize(
	ATurnManager*				InTurnManager,
	TMap<FIntPoint, ABG_Tile*>* InTileMap)
{
	TurnManager = InTurnManager;
	TileMapPtr = InTileMap;
}

void ATroopSpawner::SpawnTroop(TSubclassOf<AOccupant_BaseClass> Occupant, ABG_Tile* Tile)
{
	if (!TurnManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("TurnManager not assigned; cannot spawn troop."));
		return;
	}

	SpawnTroop(Occupant, Tile, TurnManager->GetActivePlayer());
}

void ATroopSpawner::SpawnTroop(TSubclassOf<AOccupant_BaseClass> Occupant, ABG_Tile* Tile, EActivePlayerSide OwningPlayer)
{
	if (!Occupant || !Tile)
		return;
	UWorld* World = GetWorld();
	if (!World)
		return;

	AOccupant_BaseClass* OccupantCDO = Occupant->GetDefaultObject<AOccupant_BaseClass>();
	if (!OccupantCDO)
		return;

	if (OccupantCDO->IsBuilding() && (!Tile->getBuildingCanBePlacedOnTile() || Tile->getHasBuilding()))
		return;

	if (OccupantCDO->IsTroop() && (!Tile->getCanSpawnTroopOnTile() || Tile->GetIsOccupied()))
		return;

	const FName SpawnSocketName = OccupantCDO->IsBuilding()
		? TEXT("BuildingSpawnSocket")
		: (OwningPlayer == EActivePlayerSide::PlayerA
				  ? TEXT("TroopSpawnSocket_PlayerA")
				  : (OwningPlayer == EActivePlayerSide::PlayerB
							? TEXT("TroopSpawnSocket_PlayerB")
							: (OwningPlayer == EActivePlayerSide::PlayerC
									  ? TEXT("TroopSpawnSocket_PlayerC")
									  : (OwningPlayer == EActivePlayerSide::PlayerD
												? TEXT("TroopSpawnSocket_PlayerD")
												: TEXT("TroopSpawnSocket")))));

	FVector	   SpawnLocation = Tile->GetActorLocation();
	FTransform SpawnTransform(FRotator::ZeroRotator, SpawnLocation);

	AOccupant_BaseClass* SpawnedOccupant = World->SpawnActor<AOccupant_BaseClass>(Occupant, SpawnTransform);
	if (!SpawnedOccupant)
		return;

	SpawnedOccupant->AttachToComponent(
		Tile->tileMesh,
		FAttachmentTransformRules::SnapToTargetNotIncludingScale,
		SpawnSocketName);

	SpawnedOccupant->SetGridPosition(Tile->GetGridCoordinates());
	SpawnedOccupant->SetOwningPlayer(OwningPlayer);

	if (AOccupant_Troop_BaseClass* Troop = Cast<AOccupant_Troop_BaseClass>(SpawnedOccupant))
	{
		Tile->SetOccupyingTroop(Troop);
		Tile->SetIsOccupied(true);
		Troop->SetOwningTile(Tile);
	}
	else if (AOccupant_Building_BaseClass* Building = Cast<AOccupant_Building_BaseClass>(SpawnedOccupant))
	{
		Building->SetOwningPlayer(OwningPlayer);
		Tile->SetOccupyingBuilding(Building);
		Tile->setHasBuilding(true);
	}

	Tile->SetOwningPlayer(OwningPlayer);
}

void ATroopSpawner::SpawnStartingTroops(const TArray<TArray<ABG_Tile*>>& TileGrid, int32 Cols, int32 Rows)
{
	int32 NumPlayers = 4;
	if (!StartingTroopClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("StartingTroopClass not set in TroopSpawner!"));
		return;
	}

	if (TileGrid.Num() == 0 || TileGrid[0].Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("TileGrid is empty; cannot spawn starting troops."));
		return;
	}

	TSet<ABG_Tile*> UsedSpawnTiles;

	auto IsSpawnable = [&UsedSpawnTiles](ABG_Tile* Tile) -> bool {
		return Tile && Tile->getCanSpawnTroopOnTile() && !Tile->GetIsOccupied()
			&& !UsedSpawnTiles.Contains(Tile);
	};

	auto FindSpawnFromCorner = [&TileGrid, Cols, Rows, &IsSpawnable](const FIntPoint& Corner) -> ABG_Tile* {
		if (TileGrid.IsValidIndex(Corner.Y) && TileGrid[Corner.Y].IsValidIndex(Corner.X))
		{
			ABG_Tile* CornerTile = TileGrid[Corner.Y][Corner.X];
			if (IsSpawnable(CornerTile))
				return CornerTile;
		}

		const bool bLeft = Corner.X == 0;
		const bool bTop = Corner.Y == 0;

		if (bTop)
		{
			const int32 StartCol = bLeft ? 0 : Cols - 1;
			const int32 EndCol = bLeft ? Cols : -1;
			const int32 StepCol = bLeft ? 1 : -1;

			for (int32 Col = StartCol; Col != EndCol; Col += StepCol)
			{
				ABG_Tile* Tile = TileGrid[0][Col];
				if (IsSpawnable(Tile))
					return Tile;
			}
		}
		else
		{
			const int32 StartCol = bLeft ? 0 : Cols - 1;
			const int32 EndCol = bLeft ? Cols : -1;
			const int32 StepCol = bLeft ? 1 : -1;

			for (int32 Col = StartCol; Col != EndCol; Col += StepCol)
			{
				ABG_Tile* Tile = TileGrid[Rows - 1][Col];
				if (IsSpawnable(Tile))
					return Tile;
			}
		}

		if (bLeft)
		{
			const int32 StartRow = bTop ? 0 : Rows - 1;
			const int32 EndRow = bTop ? Rows : -1;
			const int32 StepRow = bTop ? 1 : -1;

			for (int32 Row = StartRow; Row != EndRow; Row += StepRow)
			{
				ABG_Tile* Tile = TileGrid[Row][0];
				if (IsSpawnable(Tile))
					return Tile;
			}
		}
		else
		{
			const int32 StartRow = bTop ? 0 : Rows - 1;
			const int32 EndRow = bTop ? Rows : -1;
			const int32 StepRow = bTop ? 1 : -1;

			for (int32 Row = StartRow; Row != EndRow; Row += StepRow)
			{
				ABG_Tile* Tile = TileGrid[Row][Cols - 1];
				if (IsSpawnable(Tile))
					return Tile;
			}
		}

		return nullptr;
	};

	const FIntPoint PlayerCorners[4] = {
		{ 0, 0 },
		{ Cols - 1, 0 },
		{ Cols - 1, Rows - 1 },
		{ 0, Rows - 1 }
	};

	const EActivePlayerSide Players[4] = {
		EActivePlayerSide::PlayerA,
		EActivePlayerSide::PlayerB,
		EActivePlayerSide::PlayerC,
		EActivePlayerSide::PlayerD
	};

	const int32 MaxPlayers = FMath::Min(NumPlayers, 4);
	for (int32 i = 0; i < MaxPlayers; ++i)
	{
		ABG_Tile* SpawnTile = FindSpawnFromCorner(PlayerCorners[i]);
		if (SpawnTile)
		{
			UsedSpawnTiles.Add(SpawnTile);
			SpawnTroop(StartingTroopClass, SpawnTile, Players[i]);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No valid edge tile found for player %d."), i);
		}
	}
}