// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "tileSpawningLogic/TileHighlightState.h"
#include "TileHighlightSystem.generated.h"

class ABG_Tile;

UCLASS()
class PRODUCTIONPROJCURR_API UTileHighlightSystem : public UObject
{
	GENERATED_BODY()

public:
	void ApplyHighlightState(ETileHighlightState Highlight, ABG_Tile* Tile);
	void RemoveOutlineFromAllTiles();

	TArray<ABG_Tile*>& GetTilesWithOutline() { return TilesWithOutline; }

private:
	UPROPERTY()
	TArray<ABG_Tile*> TilesWithOutline;
};