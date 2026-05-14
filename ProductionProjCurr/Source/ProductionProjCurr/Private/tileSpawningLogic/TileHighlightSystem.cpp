#include "tileSpawningLogic/TileHighlightSystem.h"
#include "tileSpawningLogic/TileManagerHelpers.h"
#include "tileSpawningLogic/BG_Tile.h"

void UTileHighlightSystem::ApplyHighlightState(ETileHighlightState Highlight, ABG_Tile* Tile)
{
	if (!Tile)
		return;

	FLinearColor Color = TileManagerHelper_Functions::GetOutlineColor(Highlight);
	Tile->SetHighlightType(Highlight);
	Tile->addOutlineEffect(Color);
	TilesWithOutline.Add(Tile);
}

void UTileHighlightSystem::RemoveOutlineFromAllTiles()
{
	for (ABG_Tile* TileWithOutline : TilesWithOutline)
	{
		if (TileWithOutline)
		{
			TileWithOutline->removeOutlineEffect();
		}
	}
	TilesWithOutline.Empty();
}
