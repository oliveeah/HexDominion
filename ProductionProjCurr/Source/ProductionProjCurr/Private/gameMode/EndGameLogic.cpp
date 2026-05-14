#include "gameMode/EndGameLogic.h"
#include "tileSpawningLogic/TileManager.h"
#include "tileSpawningLogic/TileSpawner_Data.h"
#include "tileSpawningLogic/BG_Tile.h"
#include "gameMode/TurnManager.h"

void UEndGameLogic::Initialize(
	ATileManager*	   InTileManager,
	ATurnManager*	   InTurnManager,
	UTileSpawner_Data* InSpawnerData)
{
	TileManager = InTileManager;
	TurnManager = InTurnManager;
	SpawnerData = InSpawnerData;
}

void UEndGameLogic::SpawnCornucopia()
{
	if (!TileManager || !SpawnerData || !SpawnerData->CornucopiaTile)
	{
		UE_LOG(LogTemp, Warning, TEXT("EndGameLogic: Cannot spawn cornucopia � missing references."));
		return;
	}

	UWorld* World = TileManager->GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Warning, TEXT("EndGameLogic: No world context."));
		return;
	}

	const int32		CentreCol = TileManager->GridWidth / 2;
	const int32		CentreRow = TileManager->GridHeight / 2;
	const FIntPoint CentreCoords(CentreCol, CentreRow);

	ABG_Tile** Found = TileManager->TileMap.Find(CentreCoords);
	if (!Found || !(*Found))
	{
		UE_LOG(LogTemp, Warning, TEXT("EndGameLogic: Centre tile not found at (%d, %d)."), CentreCol, CentreRow);
		return;
	}

	ABG_Tile* OldTile = *Found;

	const FVector	 ActorScale = OldTile->GetActorScale3D();
	const FVector	 MeshScale = OldTile->tileMesh ? OldTile->tileMesh->GetRelativeScale3D() : FVector::OneVector;
	const FTransform Transform = OldTile->GetActorTransform();

	OldTile->Destroy();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = TileManager;

	ABG_Tile* NewTile = World->SpawnActor<ABG_Tile>(SpawnerData->CornucopiaTile, Transform, SpawnParams);
	if (!NewTile)
	{
		UE_LOG(LogTemp, Warning, TEXT("EndGameLogic: Failed to spawn cornucopia tile."));
		return;
	}

	NewTile->SetActorScale3D(ActorScale);
	if (NewTile->tileMesh)
	{
		NewTile->tileMesh->SetRelativeScale3D(MeshScale);
	}

	NewTile->SetGridCoordinates(CentreCoords);
	NewTile->SetIsSpecialTile(true);

	TileManager->TileMap.Add(CentreCoords, NewTile);
	NewTile->OnTileSelectedDelegate.AddDynamic(TileManager, &ATileManager::OnTileClicked);
	TileManager->RegisterTile(CentreCoords, NewTile);

	CornucopiaTile = NewTile;

	UE_LOG(LogTemp, Display, TEXT("EndGameLogic: Cornucopia spawned at (%d, %d)."), CentreCol, CentreRow);
}

void UEndGameLogic::EvaluateHoldCondition(int32 CurrentTurn)
{
	if (!CornucopiaTile || !TurnManager)
		return;

	if (!CornucopiaTile->GetIsOccupied())
	{
		HoldingPlayer = EActivePlayerSide::None;
		HoldTurnCount = 0;
		return;
	}

	const EActivePlayerSide CurrentHolder = CornucopiaTile->GetOccupyingPlayer();

	if (CurrentHolder == HoldingPlayer)
	{
		++HoldTurnCount;
		UE_LOG(LogTemp, Display, TEXT("Player %d holding cornucopia for %d turn(s)"),
			static_cast<int32>(HoldingPlayer), HoldTurnCount);
	}
	else
	{
		HoldingPlayer = CurrentHolder;
		HoldTurnCount = 1;
	}

	if (HoldTurnCount >= TurnsRequiredToWin)
	{
		UE_LOG(LogTemp, Display, TEXT("Player %d wins!"), static_cast<int32>(HoldingPlayer));
		TurnManager->OnPlayerWon.Broadcast(HoldingPlayer);
	}
}
