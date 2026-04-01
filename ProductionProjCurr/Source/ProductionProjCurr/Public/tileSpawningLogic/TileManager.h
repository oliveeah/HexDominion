// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "tileSpawningLogic/TileHighlightState.h"
#include "gameMode/Enum_PlayerSide.h"
#include "gameMode/TurnManager.h"
#include "TileManager.generated.h"

// Forward declarations to break circular includes
class ABG_Tile;
class ABG_TileSpawner;
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
class PRODUCTIONPROJCURR_API ATileManager : public AActor
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:		
	ATileManager();

	/*TileDefaults*/
	TArray<TArray<ABG_Tile*>> TileGrid;

	int32 GridWidth;
	int32 GridHeight;

	UPROPERTY()
	TMap<FIntPoint, ABG_Tile*> TileMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Troop | Spawning")
	float troopSpawnHeight = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Troop | Spawning")
	TSubclassOf<AOccupant_BaseClass> StartingTroopClass;

	/*References*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ABG_Tile* SelectedTile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TurnManager")
	ATurnManager* turnManager;

	TArray<ABG_Tile*> TilesWithOutline;

	/*Input Delegate*/
	UFUNCTION()
	void OnTileClicked(ABG_Tile* Tile, bool isOccupied);

	UFUNCTION()
	void OnTroopDeath();

	UFUNCTION()
	void HandleTurnChanged(EActivePlayerSide NewActivePlayer);

	UFUNCTION()
	void HandleGridBuilt();

	EPlayerIntent		determinePlayerIntent(ABG_Tile* ClickedTile) const;
	void				removeOutlineFromAllTiles();
	void				RegisterTile(const FIntPoint& Coords, ABG_Tile* Tile);
	bool				HasTile(const FIntPoint& Coords) const;
	void				spawnTroop(TSubclassOf<AOccupant_BaseClass> Occupant, ABG_Tile* Tile);
	void				spawnTroop(TSubclassOf<AOccupant_BaseClass> Occupant, ABG_Tile* Tile, EActivePlayerSide OwningPlayer);
	void				spawnStartingTroops(int cols, int rows);


	void			    ApplyHighlightState(ETileHighlightState highlight, ABG_Tile* Tile);

	/*Getters*/
	void			  GetOccupantOwner(AOccupant_BaseClass* Occupant, EActivePlayerSide currentPlayer);
	void			  GetTileOwner(ABG_Tile* Tile, EActivePlayerSide currentPlayer);
	TArray<FIntPoint> GetAdjacentTiles(bool bIncludeDiagonals, int32 adjRange, ABG_Tile* Tile);

	/*Setters*/
	void SetGridWidth(int32 Width) { GridWidth = Width; }
	void SetGridHeight(int32 Height) { GridHeight = Height; }

	void Handle_SelectTile();
	void Handle_MoveTroop(ABG_Tile* previousTile, ABG_Tile* Tile);
	void Handle_AttackTroop(ABG_Tile* previousTile, ABG_Tile* Tile);

	protected:

};