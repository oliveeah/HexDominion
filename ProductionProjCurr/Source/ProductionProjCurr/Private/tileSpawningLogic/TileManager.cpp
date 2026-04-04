// Fill out your copyright notice in the Description page of Project Settings.

#include "tileSpawningLogic/TileManager.h"  
#include "tileSpawningLogic/TileManagerHelpers.h"
#include "tileSpawningLogic/BG_TileSpawner.h"
#include "tileSpawningLogic/BG_Tile.h"
#include "Occupant/Occupant_BaseClass.h"
#include "Occupant/Occupant_Troop_BaseClass.h"
#include "Occupant/Occupant_Building_BaseClass.h"
#include "Kismet/GameplayStatics.h" 
#include <gameMode/ProductionProjCurrGameMode.h>

// Sets default values
ATileManager::ATileManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATileManager::BeginPlay()
{
	Super::BeginPlay();

	if (ABG_TileSpawner* TileSpawner = Cast<ABG_TileSpawner>(UGameplayStatics::GetActorOfClass(this, ABG_TileSpawner::StaticClass())))
	{
		TileSpawner->OnGridBuilt.AddDynamic(this, &ATileManager::HandleGridBuilt);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TileSpawner not found for grid binding!"));
	}

	if (turnManager)
	{
		turnManager->OnTurnChanged.AddDynamic(this, &ATileManager::HandleTurnChanged);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TurnManager not assigned in TileManager!"));
	}
}

void ATileManager::HandleGridBuilt()
{
	if (ABG_TileSpawner* TileSpawner = Cast<ABG_TileSpawner>(UGameplayStatics::GetActorOfClass(this, ABG_TileSpawner::StaticClass())))
	{
		TileGrid = TileSpawner->getTileGrid();
		spawnStartingTroops(TileSpawner->getNumberOfCols(), TileSpawner->getNumberOfRows());
	}
}

void ATileManager::spawnStartingTroops(int cols, int rows)
{
	int numPlayers = 4;
	if (!StartingTroopClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("StartingTroopClass not set in TileManager!"));
		return;
	}

	if (TileGrid.Num() == 0 || TileGrid[0].Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("TileGrid is empty; cannot spawn starting troops."));
		return;
	}

	TSet<ABG_Tile*> UsedSpawnTiles;

	auto IsSpawnable = [&UsedSpawnTiles](ABG_Tile* Tile) -> bool
	{
		return Tile && Tile->getCanSpawnTroopOnTile() && !Tile->GetIsOccupied()
			&& !UsedSpawnTiles.Contains(Tile);
	};

	auto FindSpawnFromCorner = [this, cols, rows, IsSpawnable](const FIntPoint& Corner) -> ABG_Tile* {
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
			const int32 StartCol = bLeft ? 0 : cols - 1;
			const int32 EndCol = bLeft ? cols : -1;
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
			const int32 StartCol = bLeft ? 0 : cols - 1;
			const int32 EndCol = bLeft ? cols : -1;
			const int32 StepCol = bLeft ? 1 : -1;

			for (int32 Col = StartCol; Col != EndCol; Col += StepCol)
			{
				ABG_Tile* Tile = TileGrid[rows - 1][Col];
				if (IsSpawnable(Tile))
					return Tile;
			}
		}

		if (bLeft)
		{
			const int32 StartRow = bTop ? 0 : rows - 1;
			const int32 EndRow = bTop ? rows : -1;
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
			const int32 StartRow = bTop ? 0 : rows - 1;
			const int32 EndRow = bTop ? rows : -1;
			const int32 StepRow = bTop ? 1 : -1;

			for (int32 Row = StartRow; Row != EndRow; Row += StepRow)
			{
				ABG_Tile* Tile = TileGrid[Row][cols - 1];
				if (IsSpawnable(Tile))
					return Tile;
			}
		}

		return nullptr;
	};
	const FIntPoint PlayerCorners[4] = {
		{ 0, 0 },					// PlayerA: top-left
		{ cols - 1, 0 },			// PlayerB: top-right
		{ cols - 1, rows - 1 },		// PlayerC: bottom-right
		{ 0, rows - 1 }				// PlayerD: bottom-left
	};

	const EActivePlayerSide Players[4] = {
		EActivePlayerSide::PlayerA,
		EActivePlayerSide::PlayerB,
		EActivePlayerSide::PlayerC,
		EActivePlayerSide::PlayerD
	};

	const int32 MaxPlayers = FMath::Min(numPlayers, 4);
	for (int32 i = 0; i < MaxPlayers; ++i)
	{
		ABG_Tile* SpawnTile = FindSpawnFromCorner(PlayerCorners[i]);
		if (SpawnTile)
		{
			UsedSpawnTiles.Add(SpawnTile);
			spawnTroop(StartingTroopClass, SpawnTile, Players[i]);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No valid edge tile found for player %d."), i);
		}
	}
}

void ATileManager::OnTileClicked(ABG_Tile* Tile, bool isOccupied)
{
	static ABG_Tile* previousTile = nullptr;

	if (!Tile)
		return;

	EPlayerIntent playerIntent = determinePlayerIntent(Tile);
	previousTile = SelectedTile;

	if (SelectedTile)
		removeOutlineFromAllTiles();

	SelectedTile = Tile;

	switch (playerIntent)
	{
		case EPlayerIntent::SelectTile:
		{
			Handle_SelectTile();

			break;
		}
		case EPlayerIntent::MoveTroop:
		{
			Handle_MoveTroop(previousTile, Tile);
			break;
		}
		case EPlayerIntent::AttackTroop:
		{
			Handle_AttackTroop(previousTile, Tile);
			break;
		}
		case EPlayerIntent::ReselectTile:
		case EPlayerIntent::Cancel:
		default:
			break;
	}

}

void ATileManager::OnTroopDeath()
{
	removeOutlineFromAllTiles();
}

void ATileManager::HandleTurnChanged(EActivePlayerSide NewActivePlayer)
{
	removeOutlineFromAllTiles();
	SelectedTile = nullptr;
}

EPlayerIntent ATileManager::determinePlayerIntent(ABG_Tile* ClickedTile) const
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
			//return EPlayerIntent::ReselectTile;

		default:
			return EPlayerIntent::SelectTile;
	}
}

void ATileManager::GetOccupantOwner(AOccupant_BaseClass* Occupant, EActivePlayerSide currentPlayer)
{
	if (Occupant)
	{
		Occupant->SetOwningPlayer(currentPlayer);
	}
}

void ATileManager::GetTileOwner(ABG_Tile* Tile, EActivePlayerSide currentPlayer)
{
	if (!Tile)
		return;

	Tile->SetOwningPlayer(currentPlayer);
}

void ATileManager::removeOutlineFromAllTiles()
{
	for (ABG_Tile* TileWithOutline : TilesWithOutline)
	{
		if (TileWithOutline)
		{
			TileWithOutline->removeOutlineEffect();
		}
	}
	TilesWithOutline.Empty();
}

TArray<FIntPoint> ATileManager::GetAdjacentTiles( bool bIncludeDiagonals, int32 adjRange, ABG_Tile* Tile)
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

bool ATileManager::HasTile(const FIntPoint& Coords) const
{
	return TileMap.Contains(Coords);
}

void ATileManager::RegisterTile(const FIntPoint& Coords, ABG_Tile* Tile)
{
	TileMap.Add(Coords, Tile);
}

void ATileManager::spawnTroop(TSubclassOf<AOccupant_BaseClass> Occupant, ABG_Tile* Tile)
{
	if (!turnManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("TurnManager not assigned; cannot spawn troop."));
		return;
	}

	spawnTroop(Occupant, Tile, turnManager->GetActivePlayer());
}

void ATileManager::spawnTroop(TSubclassOf<AOccupant_BaseClass> Occupant, ABG_Tile* Tile, EActivePlayerSide OwningPlayer)
{
	/*Ptr Checks and Setting Member vals*/
	if (!Occupant || !Tile)
		return;
	UWorld* World = GetWorld();
	if (!World)
		return;

	AOccupant_BaseClass* OccupantCDO = Occupant->GetDefaultObject<AOccupant_BaseClass>();
	if (!OccupantCDO)
		return;

	if ((OccupantCDO->IsBuilding() && !Tile->getBuildingCanBePlacedOnTile()) || (OccupantCDO->IsBuilding() && Tile->getHasBuilding()))
		return;

	if ((OccupantCDO->IsTroop() && !Tile->getCanSpawnTroopOnTile()) || (OccupantCDO->IsTroop() && Tile->GetIsOccupied()))
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

	/*Spawn and attach*/
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



void ATileManager::ApplyHighlightState(ETileHighlightState highlight, ABG_Tile* Tile)
{
	switch (highlight)
	{
		case ETileHighlightState::None:
			break;
		case ETileHighlightState::Standard:

			FLinearColor color = TileManagerHelper_Functions::GetOutlineColor(ETileHighlightState::Standard);
			Tile->SetHighlightType(ETileHighlightState::Standard);
			Tile->addOutlineEffect(color);
			TilesWithOutline.Add(Tile);

			break;
		case ETileHighlightState::Adjacency:
			Tile->SetHighlightType(ETileHighlightState::Adjacency);
			color = TileManagerHelper_Functions::GetOutlineColor(ETileHighlightState::Adjacency);
			Tile->addOutlineEffect(color);
			TilesWithOutline.Add(Tile);
			break;
		case ETileHighlightState::Attack:
			Tile->SetHighlightType(ETileHighlightState::Attack);
			color = TileManagerHelper_Functions::GetOutlineColor(ETileHighlightState::Attack);
			Tile->addOutlineEffect(color);
			TilesWithOutline.Add(Tile);
			break;
		case ETileHighlightState::Blocked:
			Tile->SetHighlightType(ETileHighlightState::Blocked);
			color = TileManagerHelper_Functions::GetOutlineColor(ETileHighlightState::Blocked);
			Tile->addOutlineEffect(color);
			TilesWithOutline.Add(Tile);
			break;
		default:
			break;
	}
}


void ATileManager::Handle_SelectTile()
{
	if (SelectedTile && SelectedTile->GetIsOccupied())
	{
		if (turnManager)
		{
			AOccupant_Troop_BaseClass* OccupyingTroop = SelectedTile->getOccupyingTroop();
			if (OccupyingTroop->TroopAnimatingAction())
			{
				removeOutlineFromAllTiles();
				return;
			}

			if (OccupyingTroop && OccupyingTroop->GetOwningPlayer() != turnManager->GetActivePlayer())
			{
				SelectedTile = nullptr;
				return;
			}
		}
	}
	PlaySoundEffect(ClickSFX, GetWorld());

	if (SelectedTile && !SelectedTile->GetIsOccupied()) // If the tile is empty, just highlight it as standard
	{
		ApplyHighlightState(ETileHighlightState::Standard, SelectedTile);
	}
	else if (SelectedTile && SelectedTile->GetIsOccupied()) // If the tile is occupied ...
	{
		TArray<FIntPoint> adjacentTiles = GetAdjacentTiles(true, 1, SelectedTile);

		for (FIntPoint Coord : adjacentTiles) // for each tile adjacent to the selected tile
		{
			if (ABG_Tile* AdjTile = TileMap[Coord])
			{
				if (AdjTile->GetIsOccupied()) // If the adjacent tile is occupied
				{
					AOccupant_Troop_BaseClass* OccupyingTroop = AdjTile->getOccupyingTroop();
					if (!OccupyingTroop) // If the occupant isn't a troop, we can't attack it, so just block the tile
					{
						ApplyHighlightState(ETileHighlightState::Blocked, AdjTile);
						continue;
					}

					if (TileManagerHelper_Functions::IsEnemyOccupant(OccupyingTroop->GetOwningPlayer(), turnManager->GetActivePlayer())) // If the occupant is an enemy, they can attack it
					{
						ApplyHighlightState(ETileHighlightState::Attack, AdjTile);
					}
					else // If the occupant is a friendly troop, we can't move there or attack it, so block the tile
					{
						ApplyHighlightState(ETileHighlightState::Blocked, AdjTile);
					}
				}
				else if (AdjTile->getCanSpawnTroopOnTile()) // If the adjacent tile isn't occupied and is a valid tile to spawn troops on, highlight it as an adjacency option
				{
					ApplyHighlightState(ETileHighlightState::Adjacency, AdjTile);
				}
				else // else block the tile, since we can't move there or spawn on it
				{
					ApplyHighlightState(ETileHighlightState::Blocked, AdjTile);
				}
			}
		}
	}
}

void ATileManager::Handle_MoveTroop(ABG_Tile* previousTile, ABG_Tile* Tile)
{
	if (!previousTile || !Tile)
		return;

	AOccupant_Troop_BaseClass* OccupyingTroop = previousTile->getOccupyingTroop();

	if (OccupyingTroop->TroopAnimatingAction())
	{
		removeOutlineFromAllTiles();
		return;
	}

	if (OccupyingTroop && OccupyingTroop->GetHealth() > 0)
	{
		PlaySoundEffect(ClickSFX, GetWorld());

		TArray<FIntPoint> adjacentTiles = GetAdjacentTiles(true, 1, previousTile);
		bool			  canMove = OccupyingTroop->CanMoveTo(Tile->GetGridCoordinates(), adjacentTiles);
		if (canMove)
		{
			OccupyingTroop->MoveToTile(Tile);
			Tile->SetOccupyingTroop(OccupyingTroop);
			Tile->SetIsOccupied(true);

			if (turnManager && Tile)
			{
				previousTile->SetOwningPlayer(EActivePlayerSide::None);
				Tile->SetOwningPlayer(turnManager->GetActivePlayer());
			}

			previousTile->SetIsOccupied(false);
		}
	}
}

void ATileManager::Handle_AttackTroop(ABG_Tile* previousTile, ABG_Tile* Tile)
{
	PlaySoundEffect(ClickSFX, GetWorld());

	if (!previousTile)
		return;

	AOccupant_Troop_BaseClass* AttackingTroop = previousTile->getOccupyingTroop();

	if (AttackingTroop->TroopAnimatingAction())
	{
		removeOutlineFromAllTiles();
		return;
	}

	AOccupant_Troop_BaseClass* DefendingTroop = Tile->getOccupyingTroop();
	if (!AttackingTroop || !DefendingTroop)
		return;

	bool ff = TileManagerHelper_Functions::IsFriendlyFire(AttackingTroop->GetOwningPlayer(), DefendingTroop->GetOwningPlayer());
	if (ff)
		return;
	AttackingTroop->SetInteractingTroop(DefendingTroop);
	DefendingTroop->SetInteractingTroop(AttackingTroop);

	AttackingTroop->SetTroopState(ETroopState::Attacking);
}

void ATileManager::PlaySoundEffect(USoundBase* Sound, UWorld* World)
{
	if (Sound && World)
	{
		UGameplayStatics::PlaySound2D(World, Sound);
	}
}
