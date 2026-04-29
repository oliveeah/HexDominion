// Fill out your copyright notice in the Description page of Project Settings.

#include "gameMode/TurnManager.h"
#include "playerData/ResourceManager.h"
// Sets default values
ATurnManager::ATurnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATurnManager::PassTurn()
{
	switch (activePlayer)
	{
		case EActivePlayerSide::PlayerA:
			activePlayer = EActivePlayerSide::PlayerB;
			UE_LOG(LogTemp, Display, TEXT("Player B is active"));
			break;
		case EActivePlayerSide::PlayerB:
			activePlayer = EActivePlayerSide::PlayerC;
			UE_LOG(LogTemp, Display, TEXT("Player C is active"));
			break;
		case EActivePlayerSide::PlayerC:
			activePlayer = EActivePlayerSide::PlayerD;
			UE_LOG(LogTemp, Display, TEXT("Player D is active"));
			break;
		case EActivePlayerSide::PlayerD:
		default:
			activePlayer = EActivePlayerSide::PlayerA;
			AllPlayersTakeTurn();
			UE_LOG(LogTemp, Display, TEXT("Player A is active"));
			break;
	}

	OnTurnChanged.Broadcast(activePlayer);
}

void ATurnManager::AllPlayersTakeTurn()
{
	currentTurn++;
	UE_LOG(LogTemp, Display, TEXT("Round complete. Current turn: %d"), currentTurn);

	if (currentTurn == MaxTurns)
	{
		// Last normal turn — broadcast regular delegate then trigger end phase
		OnAllPlayersTakenTurn.Broadcast(currentTurn);
		OnEndPhaseStarted.Broadcast();
	}
	else if (currentTurn > MaxTurns)
	{
		// End phase — one broadcast per full round for hold tracking
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
	if (ResourceManager)
	{
		const TArray<EActivePlayerSide> Players = {
			EActivePlayerSide::PlayerA,
			EActivePlayerSide::PlayerB,
			EActivePlayerSide::PlayerC,
			EActivePlayerSide::PlayerD
		};

		for (const EActivePlayerSide& Player : Players)
		{
			ResourceManager->AddBuildingMaterial(Player, 1);
			ResourceManager->AddSkillTreeCurrency(Player, currentTurn);
		}
	}
}

// Called when the game starts or when spawned
void ATurnManager::BeginPlay()
{
	Super::BeginPlay();
	
}





