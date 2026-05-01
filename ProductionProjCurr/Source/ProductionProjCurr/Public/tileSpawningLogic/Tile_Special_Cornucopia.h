// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "tileSpawningLogic/BG_Tile.h"
#include "Tile_Special_Cornucopia.generated.h"

/**
 * 
 */
UCLASS()
class PRODUCTIONPROJCURR_API ATile_Special_Cornucopia : public ABG_Tile
{
	GENERATED_BODY()
	
	public:
	virtual void UseContextAction(ATileManager* InTileManager) override;
};
