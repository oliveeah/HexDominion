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
	UseContextAction,
	Cancel
};

UCLASS()
class PRODUCTIONPROJCURR_API UTileInteractionHandler : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(
		ATurnManager*               InTurnManager,
		UTileHighlightSystem*       InHighlightSystem,
		TMap<FIntPoint, ABG_Tile*>* InTileMap);

	void OnTileClicked(ABG_Tile* Tile, bool bIsOccupied);
	void OnTroopDeath();
	void OnTurnChanged(EActivePlayerSide NewActivePlayer);

	ABG_Tile* GetSelectedTile() const { return SelectedTile; }
	void      SetDeathSFX(USoundBase* InSFX)    { DeathSFX = InSFX; }
	void      SetTeleportSFX(USoundBase* InSFX) { TeleportSFX = InSFX; }

	TArray<FIntPoint> GetAdjacentTiles(bool bIncludeDiagonals, int32 AdjRange, ABG_Tile* Tile) const;
	bool              HasTile(const FIntPoint& Coords) const;

	void BeginTeleportSelection(ABG_Tile* SourceTile, const TArray<FIntPoint>& TeleporterCoords, const TMap<FIntPoint, ABG_Tile*>& TileMap);

private:
	EPlayerIntent DeterminePlayerIntent(ABG_Tile* ClickedTile) const;

	void Handle_SelectTile();
	void Handle_MoveTroop(ABG_Tile* PreviousTile, ABG_Tile* Tile);
	void Handle_AttackTroop(ABG_Tile* PreviousTile, ABG_Tile* Tile);
	void Handle_TeleportTroop(ABG_Tile* SourceTile, ABG_Tile* DestinationTile);
	void PlaySoundEffect(USoundBase* Sound);

	UPROPERTY()
	ABG_Tile* SelectedTile = nullptr;

	UPROPERTY()
	ABG_Tile* PendingTeleportSource = nullptr;

	UPROPERTY()
	ATurnManager* TurnManager = nullptr;

	UPROPERTY()
	UTileHighlightSystem* HighlightSystem = nullptr;

	TMap<FIntPoint, ABG_Tile*>* TileMapPtr = nullptr;

	UPROPERTY()
	USoundBase* DeathSFX = nullptr;

	UPROPERTY()
	USoundBase* TeleportSFX = nullptr;
};
