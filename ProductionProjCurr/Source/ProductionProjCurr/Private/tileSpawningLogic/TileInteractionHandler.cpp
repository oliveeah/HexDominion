#include "tileSpawningLogic/TileInteractionHandler.h"
#include "tileSpawningLogic/TileHighlightSystem.h"
#include "tileSpawningLogic/TileManagerHelpers.h"
#include "tileSpawningLogic/BG_Tile.h"
#include "Occupant/Occupant_BaseClass.h"
#include "Occupant/Occupant_Troop_BaseClass.h"
#include "Occupant/MyOccupant_Troop_HealerClass.h"
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
		case EPlayerIntent::HealTroop:
			Handle_HealTroop(PreviousTile, Tile);
			break;
		case EPlayerIntent::UseContextAction:
			Handle_TeleportTroop(PendingTeleportSource, Tile);
			break;
		case EPlayerIntent::ReselectTile:
		case EPlayerIntent::Cancel:
		default:
			PendingTeleportSource = nullptr;
			SelectedTile = nullptr;
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
	PendingTeleportSource = nullptr; 
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
		case ETileHighlightState::Heal:
			return EPlayerIntent::HealTroop;
		case ETileHighlightState::Standard:
			return EPlayerIntent::ReselectTile;
		case ETileHighlightState::Teleporter:
			return EPlayerIntent::UseContextAction;
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

	if (SelectedTile && !SelectedTile->GetIsOccupied())
	{
		HighlightSystem->ApplyHighlightState(ETileHighlightState::Standard, SelectedTile);
	}
	else if (SelectedTile && SelectedTile->GetIsOccupied())
	{
		AOccupant_Troop_BaseClass* SelectedTroop = SelectedTile->getOccupyingTroop();
		const int32 AttackRange  = SelectedTroop ? SelectedTroop->GetAttackRange() : 1;
		const bool  bIsHealer    = SelectedTroop && Cast<AMyOccupant_Troop_HealerClass>(SelectedTroop) != nullptr;

		TArray<FIntPoint> MoveTiles = GetAdjacentTiles(true, 1, SelectedTile);
		for (const FIntPoint& Coord : MoveTiles)
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

				const bool bIsEnemy = TurnManager &&
					TileManagerHelper_Functions::IsEnemyOccupant(OccupyingTroop->GetOwningPlayer(), TurnManager->GetActivePlayer());

				if (bIsEnemy)
				{
					// Healers cannot attack
					if (!bIsHealer)
						HighlightSystem->ApplyHighlightState(ETileHighlightState::Attack, AdjTile);
					else
						HighlightSystem->ApplyHighlightState(ETileHighlightState::Blocked, AdjTile);
				}
				else
				{
					// Friendly — healers show Heal, others show Blocked
					if (bIsHealer && OccupyingTroop != SelectedTroop)
						HighlightSystem->ApplyHighlightState(ETileHighlightState::Heal, AdjTile);
					else
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

		// Extended attack range for non-healers
		if (AttackRange > 1 && !bIsHealer)
		{
			TArray<FIntPoint> RangeTiles = GetTilesInRange(SelectedTile, AttackRange);
			for (const FIntPoint& Coord : RangeTiles)
			{
				ABG_Tile** FoundTile = TileMapPtr->Find(Coord);
				if (!FoundTile || !(*FoundTile))
					continue;

				ABG_Tile* RangeTile = *FoundTile;
				if (RangeTile->getIsPlayingEffect())
					continue;

				if (RangeTile->GetIsOccupied())
				{
					AOccupant_Troop_BaseClass* OccupyingTroop = RangeTile->getOccupyingTroop();
					if (OccupyingTroop && TurnManager &&
						TileManagerHelper_Functions::IsEnemyOccupant(OccupyingTroop->GetOwningPlayer(), TurnManager->GetActivePlayer()))
					{
						HighlightSystem->ApplyHighlightState(ETileHighlightState::Attack, RangeTile);
					}
				}
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

	if (OccupyingTroop->GetMovesRemaining() <= 0) 
		return;


	if (OccupyingTroop->GetHealth() > 0)
	{
		TArray<FIntPoint> AdjacentTiles = GetAdjacentTiles(true, 1, PreviousTile);
		bool bCanMove = OccupyingTroop->CanMoveTo(Tile->GetGridCoordinates(), AdjacentTiles);
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

	if (AttackingTroop->GetMovesRemaining() <= 0)
		return;

	AOccupant_Troop_BaseClass* DefendingTroop = Tile->getOccupyingTroop();
	if (!DefendingTroop)
		return;

	bool bFriendlyFire = TileManagerHelper_Functions::IsFriendlyFire(AttackingTroop->GetOwningPlayer(), DefendingTroop->GetOwningPlayer());
	if (bFriendlyFire)
		return;

	PlaySoundEffect(AttackingTroop->GetAttackSound());

	AttackingTroop->SetInteractingTroop(DefendingTroop);
	DefendingTroop->SetInteractingTroop(AttackingTroop);

	AttackingTroop->SetTroopState(ETroopState::Attacking);
}

void UTileInteractionHandler::Handle_TeleportTroop(ABG_Tile* SourceTile, ABG_Tile* DestinationTile)
{
	if (!SourceTile || !DestinationTile || !HighlightSystem)
		return;

	AOccupant_Troop_BaseClass* Troop = SourceTile->getOccupyingTroop();
	if (!Troop || Troop->TroopAnimatingAction())
		return;

	PlaySoundEffect(TeleportSFX);

	Troop->TeleportToTile(DestinationTile);
	DestinationTile->SetOccupyingTroop(Troop);
	DestinationTile->SetIsOccupied(true);

	if (TurnManager)
	{
		SourceTile->SetOwningPlayer(EActivePlayerSide::None);
		DestinationTile->SetOwningPlayer(TurnManager->GetActivePlayer());
	}

	SourceTile->SetIsOccupied(false);
	SourceTile->SetOccupyingTroop(nullptr);

	PendingTeleportSource = nullptr;
	HighlightSystem->RemoveOutlineFromAllTiles();
}

void UTileInteractionHandler::BeginTeleportSelection(ABG_Tile* SourceTile, const TArray<FIntPoint>& TeleporterCoords, const TMap<FIntPoint, ABG_Tile*>& TileMap)
{
	if (!SourceTile || !HighlightSystem)
		return;

	HighlightSystem->RemoveOutlineFromAllTiles();
	PendingTeleportSource = SourceTile; 

	for (int32 i = 0; i < TeleporterCoords.Num(); ++i)
	{
		if (SourceTile->GetGridCoordinates() == TeleporterCoords[i])
			continue;

		const FIntPoint& Coords = TeleporterCoords[i];
		ABG_Tile* const* Found = TileMap.Find(Coords);
		if (Found && *Found && !(*Found)->GetIsOccupied())
		{
			HighlightSystem->ApplyHighlightState(ETileHighlightState::Teleporter, *Found);
		}
	}
}

void UTileInteractionHandler::PlaySoundEffect(USoundBase* Sound)
{
	if (!Sound)
		return;

	UGameplayStatics::PlaySound2D(this, Sound);
}

TArray<FIntPoint> UTileInteractionHandler::GetTilesInRange(ABG_Tile* Tile, int32 Range) const
{
	TArray<FIntPoint> Result;

	if (!Tile || Range <= 0)
		return Result;

	TSet<FIntPoint>   Visited;
	TArray<FIntPoint> Current;

	const FIntPoint Origin = Tile->GetGridCoordinates();
	Visited.Add(Origin);
	Current.Add(Origin);

	for (int32 Ring = 0; Ring < Range; ++Ring)
	{
		TArray<FIntPoint> Next;

		for (const FIntPoint& Coord : Current)
		{
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

			const FIntPoint* Dirs = (Coord.Y % 2 == 0) ? EvenRowDirs : OddRowDirs;

			for (int32 i = 0; i < 6; ++i)
			{
				const FIntPoint Neighbor = Coord + Dirs[i];
				if (!Visited.Contains(Neighbor) && HasTile(Neighbor))
				{
					Visited.Add(Neighbor);
					Next.Add(Neighbor);
					Result.Add(Neighbor);
				}
			}
		}

		Current = Next;
	}

	return Result;
}

void UTileInteractionHandler::Handle_HealTroop(ABG_Tile* PreviousTile, ABG_Tile* Tile)
{
	if (!PreviousTile || !Tile || !HighlightSystem)
		return;

	AOccupant_Troop_BaseClass* Healer = PreviousTile->getOccupyingTroop();
	if (!Healer || !Cast<AMyOccupant_Troop_HealerClass>(Healer))
		return;

	if (Healer->TroopAnimatingAction())
	{
		HighlightSystem->RemoveOutlineFromAllTiles();
		return;
	}

	AOccupant_Troop_BaseClass* Target = Tile->getOccupyingTroop();
	if (!Target)
		return;

	// Heal the target by 1
	const int32 NewHealth = Target->GetHealth() + 1;
	Target->SetHealth(FMath::Min(NewHealth, Target->GetTroopHealth() + 1));

	PlaySoundEffect(Healer->GetAttackSound());

	HighlightSystem->RemoveOutlineFromAllTiles();
	SelectedTile = nullptr;
}
