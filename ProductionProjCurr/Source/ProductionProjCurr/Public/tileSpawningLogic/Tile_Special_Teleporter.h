#pragma once

#include "CoreMinimal.h"
#include "tileSpawningLogic/BG_Tile.h"
#include "Tile_Special_Teleporter.generated.h"

UCLASS()
class PRODUCTIONPROJCURR_API ATile_Special_Teleporter : public ABG_Tile
{
	GENERATED_BODY()

public:
	virtual void UseContextAction(ATileManager* TileManager) override;
};
