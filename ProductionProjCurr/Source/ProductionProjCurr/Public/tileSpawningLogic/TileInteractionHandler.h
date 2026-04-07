// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "tileSpawningLogic/TileHighlightState.h"
#include "gameMode/Enum_PlayerSide.h"
#include "Sound/SoundBase.h"
#include "TileInteractionHandler.generated.h"

class ABG_Tile;
class ATurnManager;
class UTileHighlightSystem;
class AOccupant_BaseClass;

UENUM(BlueprintType)
enum class EPlayerIntent : uint8
{
	SelectTile,
	MoveTroop,
	AttackTroop,
	ReselectTile,
	Cancel
};

UCLASS()
class PRODUCTIONPROJCURR_API UTileInteractionHandler : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(
		ATurnManager*				InTurnManager,
		UTileHighlightSystem*		InHighlightSystem,
		TMap<FIntPoint, ABG_Tile*>* InTileMap);

	void OnTileClicked(ABG_Tile* Tile, bool bIsOccupied);
	void OnTroopDeath();
	void OnTurnChanged(EActivePlayerSide NewActivePlayer);

	ABG_Tile* GetSelectedTile() const { return SelectedTile; }
	void	  SetClickSFX(USoundBase* InSFX) { ClickSFX = InSFX; }

	TArray<FIntPoint> GetAdjacentTiles(bool bIncludeDiagonals, int32 AdjRange, ABG_Tile* Tile) const;
	bool			  HasTile(const FIntPoint& Coords) const;

private:
	EPlayerIntent DeterminePlayerIntent(ABG_Tile* ClickedTile) const;

	void Handle_SelectTile();
	void Handle_MoveTroop(ABG_Tile* PreviousTile, ABG_Tile* Tile);
	void Handle_AttackTroop(ABG_Tile* PreviousTile, ABG_Tile* Tile);
	void PlaySoundEffect(USoundBase* Sound);

	UPROPERTY()
	ABG_Tile* SelectedTile = nullptr;

	UPROPERTY()
	ATurnManager* TurnManager = nullptr;

	UPROPERTY()
	UTileHighlightSystem* HighlightSystem = nullptr;

	TMap<FIntPoint, ABG_Tile*>* TileMapPtr = nullptr;

	UPROPERTY()
	USoundBase* ClickSFX = nullptr;
};