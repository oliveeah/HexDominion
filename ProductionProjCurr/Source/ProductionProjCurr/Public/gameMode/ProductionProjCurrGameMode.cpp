// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProductionProjCurrGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "EngineUtils.h"
#include "GameFramework/Actor.h"
#include "tileSpawningLogic/TileManager.h"
#include "tileSpawningLogic/BG_TileSpawner.h"
#include "Data_PlayerSetUp.h"

AProductionProjCurrGameMode::AProductionProjCurrGameMode()
{
}

void AProductionProjCurrGameMode::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<ATurnManager> It(GetWorld()); It; ++It)
	{
		turnManager = *It;
		UE_LOG(LogTemp, Display, TEXT("TurnManager found and assigned!"));
		break;
	}

	if (!turnManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find TurnManager in the level!"));
	}

	for (TActorIterator<ATileManager> It(GetWorld()); It; ++It)
	{
		TileManagerInstance = *It;
		UE_LOG(LogTemp, Display, TEXT("TileManager found and assigned!"));
		break;
	}

	if (!TileManagerInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find TileManager in the level!"));
	}

	ABG_TileSpawner* TileSpawner = nullptr;
	for (TActorIterator<ABG_TileSpawner> It(GetWorld()); It; ++It)
	{
		TileSpawner = *It;
		UE_LOG(LogTemp, Display, TEXT("TileSpawner found and assigned!"));
		break;
	}

	if (TileSpawner)
	{
		TileSpawner->BuildGrid();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find TileSpawner in the level!"));
	}

	bGameActive = true;

	TurnLoop();

	InitialisePlayerUI();
}

void AProductionProjCurrGameMode::TurnLoop()
{
	if (!turnManager)
		return;

	EActivePlayerSide ActivePlayer = turnManager->GetActivePlayer();

	FString PlayerName;
	UData_PlayerSetUp* Setup = UData_PlayerSetUp::Get(this);

	if (Setup && Setup->GetActivePlayers().Num() > 0)
	{
		PlayerName = Setup->GetPlayerName(ActivePlayer);
	}
	else
	{
		// No Title Screen data — use the enum slot name as fallback
		PlayerName = FString::Printf(TEXT("Player %d"), (int32)ActivePlayer + 1);
	}

	UE_LOG(LogTemp, Display, TEXT("It is %s's turn."), *PlayerName);
}
