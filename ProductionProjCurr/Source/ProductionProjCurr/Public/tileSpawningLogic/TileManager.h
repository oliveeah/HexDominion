// Fill out your copyright notice in the Description page of Project Settings.

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

UCLASS()
class PRODUCTIONPROJCURR_API ATileManager : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	ATileManager();

	/*Grid Data*/
	TArray<TArray<ABG_Tile*>> TileGrid;

	UPROPERTY()
	TMap<FIntPoint, ABG_Tile*> TileMap;

	int32 GridWidth;
	int32 GridHeight;

	/*References — assign in editor*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TurnManager")
	ATurnManager* TurnManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Troop | Spawning")
	ATroopSpawner* TroopSpawner;

	/*Grid helpers*/
	void RegisterTile(const FIntPoint& Coords, ABG_Tile* Tile);
	bool HasTile(const FIntPoint& Coords) const;

	/*Setters*/
	void SetGridWidth(int32 Width) { GridWidth = Width; }
	void SetGridHeight(int32 Height) { GridHeight = Height; }

	/*Getters for subsystems*/
	UTileInteractionHandler* GetInteractionHandler() const { return InteractionHandler; }
	UTileHighlightSystem*	 GetHighlightSystem() const { return HighlightSystem; }
	const TArray<FIntPoint>& GetTeleporterCoords() const { return TeleporterTileCoords; }

	void RegisterTeleporterTile(const FIntPoint& Coords);

	/*Delegate handlers*/
	UFUNCTION()
	void OnTileClicked(ABG_Tile* Tile, bool bIsOccupied);

	UFUNCTION()
	void OnTroopDeath();

	UFUNCTION()
	void HandleTurnChanged(EActivePlayerSide NewActivePlayer);

	UFUNCTION()
	void HandleGridBuilt();

private:
	UPROPERTY()
	UTileHighlightSystem* HighlightSystem;

	UPROPERTY()
	UTileInteractionHandler* InteractionHandler;

	UPROPERTY(EditAnywhere, Category = "SFX")
	USoundBase* ClickSFX = nullptr;

		UPROPERTY(EditAnywhere, Category = "SFX")
	USoundBase* DeathSFX = nullptr;

	TArray<FIntPoint> TeleporterTileCoords;
};

