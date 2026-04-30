// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "gameMode/Enum_PlayerSide.h"
#include "TurnManager.h"
#include "ProductionProjCurrGameMode.generated.h"

class ATileManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnToggleTileDebugCoordinates);
/**
 *  Simple GameMode for a third person game
 */
UCLASS(abstract)
class AProductionProjCurrGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:
	
	/** Constructor */
	AProductionProjCurrGameMode();

	UPROPERTY(BlueprintAssignable, Category = "Tile Debug")
	FOnToggleTileDebugCoordinates OnToggleTileDebugCoordinates;

	UFUNCTION(BlueprintCallable, Category = "Tile Debug")
	void ToggleTileDebugCoordinates()
	{
		OnToggleTileDebugCoordinates.Broadcast();
	}

	UFUNCTION(BlueprintCallable)
	ATileManager* GetTileManager() const { return TileManagerInstance; }

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void InitialisePlayerUI();


	void TurnLoop();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TurnManager")
	ATurnManager* turnManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bGameActive;

	void SetGameActive(bool isActive) { bGameActive = isActive; }

private:
	UPROPERTY()
	ATileManager* TileManagerInstance;
};



