#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "gameMode/Enum_PlayerSide.h"
#include "TileManager.generated.h"

class ABG_Tile;
class ABG_TileSpawner;
class ATurnManager;
class ATroopSpawner;
class UTileHighlightSystem;
class UTileInteractionHandler;
class UEndGameLogic;
class AOccupant_Troop_BaseClass;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnTroopSelected, AOccupant_Troop_BaseClass*, SelectedTroop, int32, Health, int32, MovesRemaining);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTroopDeselected);

UCLASS()
class PRODUCTIONPROJCURR_API ATileManager : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	ATileManager();

	TArray<TArray<ABG_Tile*>> TileGrid;

	UPROPERTY()
	TMap<FIntPoint, ABG_Tile*> TileMap;

	int32 GridWidth;
	int32 GridHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TurnManager")
	ATurnManager* TurnManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Troop | Spawning")
	ATroopSpawner* TroopSpawner;

	UPROPERTY(BlueprintAssignable, Category = "Troop")
	FOnTroopSelected OnTroopSelected;

	UPROPERTY(BlueprintAssignable, Category = "Troop")
	FOnTroopDeselected OnTroopDeselected;

	void RegisterTile(const FIntPoint& Coords, ABG_Tile* Tile);
	bool HasTile(const FIntPoint& Coords) const;

	void SetGridWidth(int32 Width) { GridWidth = Width; }
	void SetGridHeight(int32 Height) { GridHeight = Height; }

	UTileInteractionHandler* GetInteractionHandler() const { return InteractionHandler; }
	UTileHighlightSystem*	 GetHighlightSystem() const { return HighlightSystem; }
	const TArray<FIntPoint>& GetTeleporterCoords() const { return TeleporterTileCoords; }

	void RegisterTeleporterTile(const FIntPoint& Coords);

	UFUNCTION()
	void OnTileClicked(ABG_Tile* Tile, bool bIsOccupied);

	UFUNCTION()
	void OnTroopDeath();

	UFUNCTION()
	void HandleTurnChanged(EActivePlayerSide NewActivePlayer);

	UFUNCTION()
	void HandleGridBuilt();

	UFUNCTION()
	void HandleEndPhaseStarted();

	UFUNCTION()
	void HandleEndPhaseTurn(int32 CurrentTurn);

private:
	UPROPERTY()
	UTileHighlightSystem* HighlightSystem;

	UPROPERTY()
	UTileInteractionHandler* InteractionHandler;

	UPROPERTY(EditAnywhere, Category = "SFX")
	USoundBase* ClickSFX = nullptr;

	UPROPERTY(EditAnywhere, Category = "SFX")
	USoundBase* DeathSFX = nullptr;

	UPROPERTY(EditAnywhere, Category = "SFX")
	USoundBase* TeleportSFX = nullptr;

	TArray<FIntPoint> TeleporterTileCoords;

	UPROPERTY()
	UEndGameLogic* EndGameLogic;

	// True while a troop stat panel is showing — prevents spurious deselect broadcasts
	bool bTroopCurrentlySelected = false;
};
