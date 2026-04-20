// Fill out your copyright notice in the Description page of Project Settings.

#include "tileSpawningLogic/TileInteractionHandler.h"
#include "tileSpawningLogic/TileHighlightSystem.h"
#include "tileSpawningLogic/TileManagerHelpers.h"
#include "tileSpawningLogic/BG_Tile.h"
#include "Occupant/Occupant_BaseClass.h"
#include "Occupant/Occupant_Troop_BaseClass.h"
#include "gameMode/TurnManager.h"
#include "Kismet/GameplayStatics.h"

void UTileInteractionHandler::Initialize(
	ATurnManager*				InTurnManager,
	UTileHighlightSystem*		InHighlightSystem,
	TMap<FIntPoint, ABG_Tile*>* InTileMap)
{
	TurnManager = InTurnManager;
	HighlightSystem = InHighlightSystem;
	TileMapPtr = InTileMap;
}

void UTileInteractionHandler::OnTileClicked(ABG_Tile* Tile, bool bIsOccupied)
{
	if (!Tile)
		return;

	ABG_Tile*	  PreviousTile = SelectedTile;
	EPlayerIntent PlayerIntent = DeterminePlayerIntent(Tile);

	if (SelectedTile && HighlightSystem)
		HighlightSystem->RemoveOutlineFromAllTiles();

	SelectedTile = Tile;

	switch (PlayerIntent)
	{
		case EPlayerIntent::SelectTile:
			Handle_SelectTile();
			break;
		case EPlayerIntent::MoveTroop:
			Handle_MoveTroop(PreviousTile, Tile);
			break;
		case EPlayerIntent::AttackTroop:
			Handle_AttackTroop(PreviousTile, Tile);
			break;
		case EPlayerIntent::ReselectTile:
		case EPlayerIntent::Cancel:
		default:
			break;
	}
}

void UTileInteractionHandler::OnTroopDeath()
{
	if (HighlightSystem)
		HighlightSystem->RemoveOutlineFromAllTiles();
	PlaySoundEffect(DeathSFX);
}

void UTileInteractionHandler::OnTurnChanged(EActivePlayerSide NewActivePlayer)
{
	if (HighlightSystem)
		HighlightSystem->RemoveOutlineFromAllTiles();
	SelectedTile = nullptr;
}

EPlayerIntent UTileInteractionHandler::DeterminePlayerIntent(ABG_Tile* ClickedTile) const
{
	if (!ClickedTile)
		return EPlayerIntent::Cancel;
	if (!ClickedTile->getIsPlayingEffect())
		return EPlayerIntent::SelectTile;

	switch (ClickedTile->getHighlightType())
	{
		case ETileHighlightState::Adjacency:
			return EPlayerIntent::MoveTroop;
		case ETileHighlightState::Attack:
			return EPlayerIntent::AttackTroop;
		case ETileHighlightState::Standard:
		default:
			return EPlayerIntent::SelectTile;
	}
}

TArray<FIntPoint> UTileInteractionHandler::GetAdjacentTiles(bool bIncludeDiagonals, int32 AdjRange, ABG_Tile* Tile) const
{
	TArray<FIntPoint> Neighbors;

	if (!Tile)
		return Neighbors;

	const FIntPoint SelectedCoords = Tile->GetGridCoordinates();

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

	const FIntPoint* Directions = (SelectedCoords.Y % 2 == 0) ? EvenRowDirs : OddRowDirs;

	for (int32 i = 0; i < 6; i++)
	{
		const FIntPoint Neighbor = SelectedCoords + Directions[i];

		if (HasTile(Neighbor))
		{
			Neighbors.Add(Neighbor);
		}
	}
	return Neighbors;
}

bool UTileInteractionHandler::HasTile(const FIntPoint& Coords) const
{
	return TileMapPtr && TileMapPtr->Contains(Coords);
}

void UTileInteractionHandler::Handle_SelectTile()
{
	if (!HighlightSystem || !TileMapPtr)
		return;

	if (SelectedTile && SelectedTile->GetIsOccupied())
	{
		if (TurnManager)
		{
			AOccupant_Troop_BaseClass* OccupyingTroop = SelectedTile->getOccupyingTroop();
			if (OccupyingTroop && OccupyingTroop->TroopAnimatingAction())
			{
				HighlightSystem->RemoveOutlineFromAllTiles();
				return;
			}

			if (OccupyingTroop && OccupyingTroop->GetOwningPlayer() != TurnManager->GetActivePlayer())
			{
				SelectedTile = nullptr;
				return;
			}
		}
	}

	PlaySoundEffect(ClickSFX);

	if (SelectedTile && !SelectedTile->GetIsOccupied())
	{
		HighlightSystem->ApplyHighlightState(ETileHighlightState::Standard, SelectedTile);
	}
	else if (SelectedTile && SelectedTile->GetIsOccupied())
	{
		TArray<FIntPoint> AdjacentTiles = GetAdjacentTiles(true, 1, SelectedTile);

		for (const FIntPoint& Coord : AdjacentTiles)
		{
			ABG_Tile** FoundTile = TileMapPtr->Find(Coord);
			if (!FoundTile || !(*FoundTile))
				continue;

			ABG_Tile* AdjTile = *FoundTile;

			if (AdjTile->GetIsOccupied())
			{
				AOccupant_Troop_BaseClass* OccupyingTroop = AdjTile->getOccupyingTroop();
				if (!OccupyingTroop)
				{
					HighlightSystem->ApplyHighlightState(ETileHighlightState::Blocked, AdjTile);
					continue;
				}

				if (TurnManager && TileManagerHelper_Functions::IsEnemyOccupant(OccupyingTroop->GetOwningPlayer(), TurnManager->GetActivePlayer()))
				{
					HighlightSystem->ApplyHighlightState(ETileHighlightState::Attack, AdjTile);
				}
				else
				{
					HighlightSystem->ApplyHighlightState(ETileHighlightState::Blocked, AdjTile);
				}
			}
			else if (AdjTile->getCanSpawnTroopOnTile())
			{
				HighlightSystem->ApplyHighlightState(ETileHighlightState::Adjacency, AdjTile);
			}
			else
			{
				HighlightSystem->ApplyHighlightState(ETileHighlightState::Blocked, AdjTile);
			}
		}
	}
}

void UTileInteractionHandler::Handle_MoveTroop(ABG_Tile* PreviousTile, ABG_Tile* Tile)
{
	if (!PreviousTile || !Tile || !HighlightSystem)
		return;

	AOccupant_Troop_BaseClass* OccupyingTroop = PreviousTile->getOccupyingTroop();

	if (!OccupyingTroop)
		return;

	if (OccupyingTroop->TroopAnimatingAction())
	{
		HighlightSystem->RemoveOutlineFromAllTiles();
		return;
	}

	if (OccupyingTroop->GetHealth() > 0)
	{
		PlaySoundEffect(ClickSFX);

		TArray<FIntPoint> AdjacentTiles = GetAdjacentTiles(true, 1, PreviousTile);
		bool			  bCanMove = OccupyingTroop->CanMoveTo(Tile->GetGridCoordinates(), AdjacentTiles);
		if (bCanMove)
		{
			OccupyingTroop->MoveToTile(Tile);
			PlaySoundEffect(OccupyingTroop->GetMoveSound());
			Tile->SetOccupyingTroop(OccupyingTroop);
			Tile->SetIsOccupied(true);

			if (TurnManager)
			{
				PreviousTile->SetOwningPlayer(EActivePlayerSide::None);
				Tile->SetOwningPlayer(TurnManager->GetActivePlayer());
			}

			PreviousTile->SetIsOccupied(false);
		}
	}
}

void UTileInteractionHandler::Handle_AttackTroop(ABG_Tile* PreviousTile, ABG_Tile* Tile)
{
	PlaySoundEffect(ClickSFX);

	if (!PreviousTile || !Tile || !HighlightSystem)
		return;

	AOccupant_Troop_BaseClass* AttackingTroop = PreviousTile->getOccupyingTroop();

	if (!AttackingTroop)
		return;

	if (AttackingTroop->TroopAnimatingAction())
	{
		HighlightSystem->RemoveOutlineFromAllTiles();
		return;
	}

	AOccupant_Troop_BaseClass* DefendingTroop = Tile->getOccupyingTroop();
	if (!DefendingTroop)
		return;

	bool bFriendlyFire = TileManagerHelper_Functions::IsFriendlyFire(AttackingTroop->GetOwningPlayer(), DefendingTroop->GetOwningPlayer());
	if (bFriendlyFire)
		return;

	// Play attack SFX before dealing damage (which may destroy the defender)
	PlaySoundEffect(AttackingTroop->GetAttackSound());

	AttackingTroop->SetInteractingTroop(DefendingTroop);
	DefendingTroop->SetInteractingTroop(AttackingTroop);

	AttackingTroop->SetTroopState(ETroopState::Attacking);
}

void UTileInteractionHandler::PlaySoundEffect(USoundBase* Sound)
{
	if (!Sound)
		return;

	UGameplayStatics::PlaySound2D(this, Sound);
}