#include "tileSpawningLogic/TileManager.h"
#include "tileSpawningLogic/TileHighlightSystem.h"
#include "tileSpawningLogic/TileInteractionHandler.h"
#include "tileSpawningLogic/BG_TileSpawner.h"
#include "tileSpawningLogic/BG_Tile.h"
#include "Occupant/TroopSpawner.h"
#include "Occupant/Occupant_Troop_BaseClass.h"
#include "Occupant/Occupant_Building_BaseClass.h"
#include "gameMode/TurnManager.h"
#include "gameMode/EndGameLogic.h"
#include "Kismet/GameplayStatics.h"

ATileManager::ATileManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATileManager::BeginPlay()
{
	Super::BeginPlay();

	HighlightSystem = NewObject<UTileHighlightSystem>(this);
	InteractionHandler = NewObject<UTileInteractionHandler>(this);
	EndGameLogic = NewObject<UEndGameLogic>(this);

	InteractionHandler->Initialize(TurnManager, HighlightSystem, &TileMap);
	InteractionHandler->SetDeathSFX(DeathSFX);
	InteractionHandler->SetTeleportSFX(TeleportSFX);

	if (TroopSpawner)
	{
		TroopSpawner->Initialize(TurnManager, &TileMap);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TroopSpawner not assigned in TileManager!"));
	}

	if (ABG_TileSpawner* TileSpawner = Cast<ABG_TileSpawner>(
			UGameplayStatics::GetActorOfClass(this, ABG_TileSpawner::StaticClass())))
	{
		TileSpawner->OnGridBuilt.AddDynamic(this, &ATileManager::HandleGridBuilt);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TileSpawner not found for grid binding!"));
	}

	if (TurnManager)
	{
		TurnManager->OnTurnChanged.AddDynamic(this, &ATileManager::HandleTurnChanged);
		TurnManager->OnEndPhaseStarted.AddDynamic(this, &ATileManager::HandleEndPhaseStarted);
		TurnManager->OnEndPhaseTurn.AddDynamic(this, &ATileManager::HandleEndPhaseTurn);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TurnManager not assigned in TileManager!"));
	}
}

void ATileManager::HandleGridBuilt()
{
	if (ABG_TileSpawner* TileSpawner = Cast<ABG_TileSpawner>(
			UGameplayStatics::GetActorOfClass(this, ABG_TileSpawner::StaticClass())))
	{
		TileGrid = TileSpawner->getTileGrid();

		if (EndGameLogic)
		{
			UTileSpawner_Data* SpawnerData = TileSpawner->GetTileSpawnerData();
			EndGameLogic->Initialize(this, TurnManager, SpawnerData);
		}

		if (TroopSpawner)
		{
			TroopSpawner->SpawnStartingTroops(
				TileGrid,
				TileSpawner->getNumberOfCols(),
				TileSpawner->getNumberOfRows());
		}
	}
}

void ATileManager::OnTileClicked(ABG_Tile* Tile, bool bIsOccupied)
{
	if (InteractionHandler)
		InteractionHandler->OnTileClicked(Tile, bIsOccupied);
}

void ATileManager::OnTroopDeath()
{
	if (InteractionHandler)
		InteractionHandler->OnTroopDeath();
}

void ATileManager::HandleTurnChanged(EActivePlayerSide NewActivePlayer)
{
	for (auto& Pair : TileMap)
	{
		ABG_Tile* Tile = Pair.Value;
		if (!Tile || !Tile->GetIsOccupied())
			continue;

		AOccupant_Troop_BaseClass* Troop = Tile->getOccupyingTroop();
		if (Troop && Troop->GetOwningPlayer() == NewActivePlayer)
		{
			Troop->ResetMoves();
		}
	}

	// Spawn a troop on every building tile owned by the new active player that is unoccupied
	if (TroopSpawner && TroopSpawner->BuildingProductionTroopClass)
	{
		for (auto& Pair : TileMap)
		{
			ABG_Tile* Tile = Pair.Value;
			if (!Tile)
				continue;

			if (!Tile->getHasBuilding())
				continue;

			if (Tile->GetIsOccupied())
				continue;

			// Check the building's owner directly — tile ownership is cleared when troops move off
			AOccupant_Building_BaseClass* Building = Tile->getOccupyingBuilding();
			if (!Building || Building->GetOwningPlayer() != NewActivePlayer)
				continue;

			TroopSpawner->SpawnTroop(TroopSpawner->BuildingProductionTroopClass, Tile, NewActivePlayer);

			UE_LOG(LogTemp, Display, TEXT("Building produced a troop at (%d, %d) for player %d."),
				Tile->GetGridCoordinates().X, Tile->GetGridCoordinates().Y, (int32)NewActivePlayer);
		}
	}

	if (InteractionHandler)
		InteractionHandler->OnTurnChanged(NewActivePlayer);
}

void ATileManager::RegisterTile(const FIntPoint& Coords, ABG_Tile* Tile)
{
	TileMap.Add(Coords, Tile);
}

bool ATileManager::HasTile(const FIntPoint& Coords) const
{
	return TileMap.Contains(Coords);
}

void ATileManager::RegisterTeleporterTile(const FIntPoint& Coords)
{
	TeleporterTileCoords.AddUnique(Coords);
	UE_LOG(LogTemp, Log, TEXT("Teleporter registered at (%d, %d). Total: %d"), Coords.X, Coords.Y, TeleporterTileCoords.Num());
}

void ATileManager::HandleEndPhaseStarted()
{
	if (EndGameLogic)
		EndGameLogic->SpawnCornucopia();
}

void ATileManager::HandleEndPhaseTurn(int32 CurrentTurn)
{
	if (EndGameLogic)
		EndGameLogic->EvaluateHoldCondition(CurrentTurn);
}
