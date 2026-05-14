#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "gameMode/Enum_PlayerSide.h"
#include "TurnManager.generated.h"

class AResourceManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTurnChanged, EActivePlayerSide, NewActivePlayer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAllPlayersTakenTurn, int32, CurrentTurn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndPhaseStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEndPhaseTurn, int32, CurrentTurn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerWon, EActivePlayerSide, WinningPlayer);

UCLASS()
class PRODUCTIONPROJCURR_API ATurnManager : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY()
	EActivePlayerSide activePlayer = EActivePlayerSide::PlayerA;

	static constexpr int MaxTurns = 10;

	TArray<EActivePlayerSide> ActivePlayerOrder;

	int32 CurrentPlayerIndex = 0;

public:
	UPROPERTY(BlueprintAssignable, Category = "TurnManager")
	FOnTurnChanged OnTurnChanged;

	UPROPERTY(BlueprintAssignable, Category = "TurnManager")
	FOnAllPlayersTakenTurn OnAllPlayersTakenTurn;

	UPROPERTY(BlueprintAssignable, Category = "TurnManager")
	FOnEndPhaseStarted OnEndPhaseStarted;

	UPROPERTY(BlueprintAssignable, Category = "TurnManager")
	FOnEndPhaseTurn OnEndPhaseTurn;

	UPROPERTY(BlueprintAssignable, Category = "TurnManager")
	FOnPlayerWon OnPlayerWon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TurnManager")
	int currentTurn = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	AResourceManager* ResourceManager;

protected:
	virtual void BeginPlay() override;

public:
	ATurnManager();

	UFUNCTION()
	void PassTurn();

	EActivePlayerSide GetActivePlayer() const { return activePlayer; }

	UFUNCTION()
	void AllPlayersTakeTurn();

	void GiveAllPlayersResourcesForNewTurn();
};
