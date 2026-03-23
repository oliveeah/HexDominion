// Fill out your copyright notice in the Description page of Project Settings.

#include "tileSpawningLogic/TileManager.h"  
#include "tileSpawningLogic/BG_TileSpawner.h"
#include "tileSpawningLogic/BG_Tile.h"
#include "Occupant/Occupant_BaseClass.h"
#include "Occupant/Occupant_Troop_BaseClass.h"
#include "Occupant/Occupant_Building_BaseClass.h"
#include "Kismet/GameplayStatics.h" // For GetActorOfClass
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
	int numPlayers = 2;
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

	auto IsSpawnable = [](ABG_Tile* Tile) -> bool
	{
		return Tile && Tile->getCanSpawnTroopOnTile() && !Tile->isOccupied;
	};

	auto FindSpawnFromCorner = [this, cols, rows, IsSpawnable](const FIntPoint& Corner) -> ABG_Tile*
	{
		if (TileGrid.IsValidIndex(Corner.Y) && TileGrid[Corner.Y].IsValidIndex(Corner.X))
		{
			ABG_Tile* CornerTile = TileGrid[Corner.Y][Corner.X];
			if (IsSpawnable(CornerTile))
				return CornerTile;
		}

		const bool bLeft = Corner.X == 0;
		const bool bTop = Corner.Y == 0;

		// Scan along horizontal edge from the corner
		if (bTop)
		{
			for (int32 Col = 0; Col < cols; ++Col)
			{
				ABG_Tile* Tile = TileGrid[0][Col];
				if (IsSpawnable(Tile))
					return Tile;
			}
		}
		else // if bottom edge
		{
			for (int32 Col = 0; Col < cols; ++Col)
			{
				ABG_Tile* Tile = TileGrid[rows - 1][Col];
				if (IsSpawnable(Tile))
					return Tile;
			}
		}

		// Scan along vertical edge from the corner
		if (bLeft)
		{
			for (int32 Row = 0; Row < rows; ++Row)
			{
				ABG_Tile* Tile = TileGrid[Row][0];
				if (IsSpawnable(Tile))
					return Tile;
			}
		}
		else // if right edge
		{
			for (int32 Row = 0; Row < rows; ++Row)
			{
				ABG_Tile* Tile = TileGrid[Row][cols - 1];
				if (IsSpawnable(Tile))
					return Tile;
			}
		}

		return nullptr;
	};

	const FIntPoint PlayerCorners[2] = {
		{ 0, 0 },                 // PlayerA: top-left
		{ cols - 1, rows - 1 }    // PlayerB: bottom-right
	};

	const int32 MaxPlayers = FMath::Min(numPlayers, 2);
	for (int32 i = 0; i < MaxPlayers; ++i)
	{
		ABG_Tile* SpawnTile = FindSpawnFromCorner(PlayerCorners[i]);
		if (SpawnTile)
		{
			EActivePlayerSide Player = (i == 0) ? EActivePlayerSide::PlayerA : EActivePlayerSide::PlayerB;
			spawnTroop(StartingTroopClass, SpawnTile, Player);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No valid edge tile found for player %d."), i);
		}
	}
}

// Called every frame
void ATileManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FString& ATileManager::GetSelectedTileCoordinates()
{
	static FString coords = TEXT("N/A");
		if (SelectedTile)
		{
			coords = FString::Printf(TEXT("(%d, %d)"), (int)SelectedTile->getGridCoordinates().X, (int)SelectedTile->getGridCoordinates().Y);
		}
		else
		{
			coords = TEXT("N/A");
		}
	return coords;
}

void ATileManager::OnTileClicked(ABG_Tile* Tile, bool isOccupied)
{
	static ABG_Tile* previousTile = nullptr;

	if (!Tile)
		return;

	EPlayerIntent playerIntent = determinePlayerIntent(Tile);
	previousTile = SelectedTile;

	if (SelectedTile)
	{
		removeOutlineFromAllTiles();
	}

	SelectedTile = Tile;

	switch (playerIntent)
	{
		case EPlayerIntent::SelectTile:
		{
			if (SelectedTile && SelectedTile->GetIsOccupied())
			{
				if (turnManager)
				{
					AOccupant_Troop_BaseClass* OccupyingTroop = SelectedTile->getOccupyingTroop();
					if (OccupyingTroop && OccupyingTroop->GetOwningPlayer() != turnManager->GetActivePlayer())
					{
						SelectedTile = nullptr;
						return;
					}
				}
			}

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
							if (!OccupyingTroop)									 // If the occupant isn't a troop, we can't attack it, so just block the tile
							{
								ApplyHighlightState(ETileHighlightState::Blocked, AdjTile);
								continue;
							}

							if (IsEnemyOccupant(OccupyingTroop->GetOwningPlayer())) // If the occupant is an enemy, they can attack it
							{
								ApplyHighlightState(ETileHighlightState::Attack, AdjTile);
							}
							else													// If the occupant is a friendly troop, we can't move there or attack it, so block the tile
							{
								ApplyHighlightState(ETileHighlightState::Blocked, AdjTile);
							}
						}
						else if (AdjTile->getCanSpawnTroopOnTile())					// If the adjacent tile isn't occupied and is a valid tile to spawn troops on, highlight it as an adjacency option
						{
							ApplyHighlightState(ETileHighlightState::Adjacency, AdjTile);
						}
						else														// else block the tile, since we can't move there or spawn on it
						{
							ApplyHighlightState(ETileHighlightState::Blocked, AdjTile);
						}
					}
				}
			}

			break;
		}
		case EPlayerIntent::MoveTroop:
		{
			if (!previousTile)
				break;

			AOccupant_Troop_BaseClass* OccupyingTroop = previousTile->getOccupyingTroop();
			if (OccupyingTroop && OccupyingTroop->GetHealth() > 0)
			{
				TArray<FIntPoint> adjacentTiles = GetAdjacentTiles(true, 1, previousTile);
				bool canMove = OccupyingTroop->CanMoveTo(Tile->getGridCoordinates(), adjacentTiles);
				if (canMove)
				{
					OccupyingTroop->MoveToTile(Tile);
					Tile->SetOccupyingTroop(OccupyingTroop);
					Tile->isOccupied = true;

					if (turnManager && Tile)
					{
						previousTile->SetOwningPlayer(EActivePlayerSide::None);
						Tile->SetOwningPlayer(turnManager->GetActivePlayer());
					}

					previousTile->isOccupied = false;
				}
			}

			break;
		}
		case EPlayerIntent::AttackTroop:
		{
			if (!previousTile)
				break;

			AOccupant_Troop_BaseClass* AttackingTroop = previousTile->getOccupyingTroop();
			AOccupant_Troop_BaseClass* DefendingTroop = Tile->getOccupyingTroop();
			if (!AttackingTroop || !DefendingTroop)
				break;

			bool ff = IsFriendlyFire(AttackingTroop->GetOwningPlayer(), DefendingTroop->GetOwningPlayer());
			if (ff)
				break;

			AttackingTroop->SetIsAttacking(true);
			DefendingTroop->SetHealth(0);
			Tile->isOccupied = false;

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

	const FIntPoint SelectedCoords = Tile->getGridCoordinates();

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

	if ((OccupantCDO->IsTroop() && !Tile->getCanSpawnTroopOnTile()) || (OccupantCDO->IsTroop() && Tile->isOccupied))
		return;

	const FName SpawnSocketName = OccupantCDO->IsBuilding()
		? TEXT("BuildingSpawnSocket")
		: TEXT("TroopSpawnSocket");

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

	SpawnedOccupant->SetGridPosition(Tile->getGridCoordinates());
	SpawnedOccupant->SetOwningPlayer(OwningPlayer);

	if (AOccupant_Troop_BaseClass* Troop = Cast<AOccupant_Troop_BaseClass>(SpawnedOccupant))
	{
		Troop->OnTroopDeath.AddDynamic(this, &ATileManager::OnTroopDeath);
		Tile->SetOccupyingTroop(Troop);
		Tile->isOccupied = true;
	}
	else if (AOccupant_Building_BaseClass* Building = Cast<AOccupant_Building_BaseClass>(SpawnedOccupant))
	{
		Building->SetOwningPlayer(OwningPlayer);
		Tile->SetOccupyingBuilding(Building);
		Tile->setHasBuilding(true);
	}

	Tile->SetOwningPlayer(OwningPlayer);
}

bool ATileManager::IsFriendlyFire(EActivePlayerSide attackingPlayerID, EActivePlayerSide targetPlayerID)
{
	if (attackingPlayerID == targetPlayerID)
	{
		return true; // Friendly fire
	}
	else
	{
		return false; // Not friendly fire
	}
}

bool ATileManager::IsEnemyOccupant(EActivePlayerSide troopToCheck)
{
	if (troopToCheck != turnManager->GetActivePlayer() && troopToCheck != EActivePlayerSide::None)
	{
		return true; // Enemy occupant
	}
	else
	{
		return false; // Not an enemy occupant
	}
}

void ATileManager::ApplyHighlightState(ETileHighlightState highlight, ABG_Tile* Tile)
{
	switch (highlight)
	{
		case ETileHighlightState::None:
			break;
		case ETileHighlightState::Standard:

			FLinearColor color = GetOutlineColor(ETileHighlightState::Standard);
			Tile->SetHighlightType(ETileHighlightState::Standard);
			Tile->addOutlineEffect(color);
			TilesWithOutline.Add(Tile);

			break;
		case ETileHighlightState::Adjacency:
			Tile->SetHighlightType(ETileHighlightState::Adjacency);
			color = GetOutlineColor(ETileHighlightState::Adjacency);
			Tile->addOutlineEffect(color);
			TilesWithOutline.Add(Tile);
			break;
		case ETileHighlightState::Attack:
			Tile->SetHighlightType(ETileHighlightState::Attack);
			color = GetOutlineColor(ETileHighlightState::Attack);
			Tile->addOutlineEffect(color);
			TilesWithOutline.Add(Tile);
			break;
		case ETileHighlightState::Blocked:
			Tile->SetHighlightType(ETileHighlightState::Blocked);
			color = GetOutlineColor(ETileHighlightState::Blocked);
			Tile->addOutlineEffect(color);
			TilesWithOutline.Add(Tile);
			break;
		default:
			break;
	}
}

FLinearColor ATileManager::GetOutlineColor(ETileHighlightState highlightState) const
{
	switch (highlightState)
	{
		case ETileHighlightState::Standard:
			return FLinearColor(0, 0, 0, 1); // black

		case ETileHighlightState::Adjacency:
			return FLinearColor(0.002000, 0.010000, 0.030000, 1.000000); // Darker Blue

		case ETileHighlightState::Attack:
			return FLinearColor(2.000000, 0, 0, 1); // Darker Red

		case ETileHighlightState::Blocked:
			return FLinearColor(5, 5, 5, 1); // White
		default:
			return FLinearColor(5, 5, 5, 1); // White
	}
}

