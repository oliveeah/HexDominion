// Fill out your copyright notice in the Description page of Project Settings.

#include "gameMode/TurnManager.h"
#include "playerData/ResourceManager.h"
#include "Data_PlayerSetUp.h"

ATurnManager::ATurnManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATurnManager::BeginPlay()
{
	Super::BeginPlay();

	// Build the turn order from whoever was set up on the Title Screen
	UData_PlayerSetUp* Setup = UData_PlayerSetUp::Get(this);
	if (Setup && Setup->GetActivePlayers().Num() > 0)
	{
		for (const FPlayerEntry& Entry : Setup->GetActivePlayers())
		{
			ActivePlayerOrder.Add(Entry.PlayerSide);
		}
		UE_LOG(LogTemp, Display, TEXT("TurnManager: %d players in turn order."), ActivePlayerOrder.Num());
	}
	else
	{
		// Fallback: all 4 players (e.g. playing without a Title Screen)
		ActivePlayerOrder = {
			EActivePlayerSide::PlayerA,
			EActivePlayerSide::PlayerB,
			EActivePlayerSide::PlayerC,
			EActivePlayerSide::PlayerD
		};
		UE_LOG(LogTemp, Warning, TEXT("TurnManager: No setup data found — defaulting to 4 players."));
	}

	CurrentPlayerIndex = 0;
	activePlayer       = ActivePlayerOrder[0];
}

void ATurnManager::PassTurn()
{
	if (ActivePlayerOrder.Num() == 0)
		return;

	CurrentPlayerIndex = (CurrentPlayerIndex + 1) % ActivePlayerOrder.Num();
	activePlayer       = ActivePlayerOrder[CurrentPlayerIndex];

	UE_LOG(LogTemp, Display, TEXT("Turn passed - now: %d (index %d of %d)"),
		(int32)activePlayer, CurrentPlayerIndex, ActivePlayerOrder.Num());

	// Completed a full round when we wrap back to the first player
	if (CurrentPlayerIndex == 0)
	{
		AllPlayersTakeTurn();
	}

	OnTurnChanged.Broadcast(activePlayer);
}

void ATurnManager::AllPlayersTakeTurn()
{
	currentTurn++;
	UE_LOG(LogTemp, Display, TEXT("Round complete. Current turn: %d"), currentTurn);

	if (currentTurn == MaxTurns)
	{
		OnAllPlayersTakenTurn.Broadcast(currentTurn);
		OnEndPhaseStarted.Broadcast();
	}
	else if (currentTurn > MaxTurns)
	{
		OnEndPhaseTurn.Broadcast(currentTurn);
	}
	else
	{
		OnAllPlayersTakenTurn.Broadcast(currentTurn);
	}

	GiveAllPlayersResourcesForNewTurn();
}

void ATurnManager::GiveAllPlayersResourcesForNewTurn()
{
	if (!ResourceManager)
		return;

	// Only give resources to players actually in this game
	for (const EActivePlayerSide& Player : ActivePlayerOrder)
	{
		ResourceManager->AddBuildingMaterial(Player, 1);
		ResourceManager->AddSkillTreeCurrency(Player, currentTurn);
	}
}





