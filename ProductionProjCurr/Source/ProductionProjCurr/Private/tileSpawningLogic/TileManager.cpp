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
	if (!InteractionHandler)
		return;

	InteractionHandler->OnTileClicked(Tile, bIsOccupied);

	if (InteractionHandler->GetLastIntent() == EPlayerIntent::SelectTile)
	{
		if (Tile && Tile->GetIsOccupied())
		{
			AOccupant_Troop_BaseClass* Troop = Tile->getOccupyingTroop();
			if (Troop)
			{
				bTroopCurrentlySelected = true;
				OnTroopSelected.Broadcast(Troop, Troop->GetTroopHealth(), Troop->GetMovesRemaining());
				return;
			}
		}
	}

	// Only broadcast deselect if the panel was actually shown
	if (bTroopCurrentlySelected)
	{
		bTroopCurrentlySelected = false;
		OnTroopDeselected.Broadcast();
	}
}

void ATileManager::OnTroopDeath()
{
	if (InteractionHandler)
		InteractionHandler->OnTroopDeath();

	if (bTroopCurrentlySelected)
	{
		bTroopCurrentlySelected = false;
		OnTroopDeselected.Broadcast();
	}
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

	if (TroopSpawner)
	{
		for (auto& Pair : TileMap)
		{
			ABG_Tile* Tile = Pair.Value;
			if (!Tile || !Tile->getHasBuilding() || Tile->GetIsOccupied())
				continue;

			AOccupant_Building_BaseClass* Building = Tile->getOccupyingBuilding();
			if (!Building || Building->GetOwningPlayer() != NewActivePlayer)
				continue;

			// Pick the troop class based on what the player chose when they built
			TSubclassOf<AOccupant_BaseClass> TroopClass = nullptr;

			switch (Building->ProductionType)
			{
				case EBuildingProductionType::MeleeTroop:
					TroopClass = TroopSpawner->ProductionTroopClass_Melee;
					break;
				case EBuildingProductionType::RangedTroop:
					TroopClass = TroopSpawner->ProductionTroopClass_Ranged;
					break;
				case EBuildingProductionType::SupportTroop:
					TroopClass = TroopSpawner->ProductionTroopClass_Support;
					break;
				default:
					TroopClass = TroopSpawner->BuildingProductionTroopClass;
					break;
			}

			if (!TroopClass)
				continue;

			TroopSpawner->SpawnTroopFromBuilding(TroopClass, Tile, NewActivePlayer);

			UE_LOG(LogTemp, Display, TEXT("Building at (%d,%d) produced option %d for player %d."),
				Tile->GetGridCoordinates().X, Tile->GetGridCoordinates().Y,
				(int32)Building->ProductionType, (int32)NewActivePlayer);
		}
	}

	if (InteractionHandler)
		InteractionHandler->OnTurnChanged(NewActivePlayer);

	if (bTroopCurrentlySelected)
	{
		bTroopCurrentlySelected = false;
		OnTroopDeselected.Broadcast();
	}
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
