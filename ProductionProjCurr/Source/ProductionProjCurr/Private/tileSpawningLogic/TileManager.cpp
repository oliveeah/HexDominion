// Fill out your copyright notice in the Description page of Project Settings.

#include "tileSpawningLogic/TileManager.h"
#include "tileSpawningLogic/TileHighlightSystem.h"
#include "tileSpawningLogic/TileInteractionHandler.h"
#include "tileSpawningLogic/BG_TileSpawner.h"
#include "tileSpawningLogic/BG_Tile.h"
#include "Occupant/TroopSpawner.h"
#include "gameMode/TurnManager.h"
#include "Kismet/GameplayStatics.h"

ATileManager::ATileManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATileManager::BeginPlay()
{
	Super::BeginPlay();

	// Create subsystems
	HighlightSystem = NewObject<UTileHighlightSystem>(this);
	InteractionHandler = NewObject<UTileInteractionHandler>(this);

	InteractionHandler->Initialize(TurnManager, HighlightSystem, &TileMap);
	InteractionHandler->SetClickSFX(ClickSFX);
	InteractionHandler->SetDeathSFX(DeathSFX);

	if (TroopSpawner)
	{
		TroopSpawner->Initialize(TurnManager, &TileMap);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TroopSpawner not assigned in TileManager!"));
	}

	// Bind grid-built delegate
	if (ABG_TileSpawner* TileSpawner = Cast<ABG_TileSpawner>(
			UGameplayStatics::GetActorOfClass(this, ABG_TileSpawner::StaticClass())))
	{
		TileSpawner->OnGridBuilt.AddDynamic(this, &ATileManager::HandleGridBuilt);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TileSpawner not found for grid binding!"));
	}

	// Bind turn-changed delegate
	if (TurnManager)
	{
		TurnManager->OnTurnChanged.AddDynamic(this, &ATileManager::HandleTurnChanged);
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