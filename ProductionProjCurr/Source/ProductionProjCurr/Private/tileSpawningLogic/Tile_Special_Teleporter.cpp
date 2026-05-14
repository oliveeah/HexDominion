#include "tileSpawningLogic/Tile_Special_Teleporter.h"
#include "tileSpawningLogic/TileManager.h"
#include "tileSpawningLogic/TileInteractionHandler.h"

void ATile_Special_Teleporter::UseContextAction(ATileManager* TileManager)
{
	if (!TileManager || !GetIsOccupied())
		return;

	UTileInteractionHandler* InteractionHandlerRef = TileManager->GetInteractionHandler();
	if (!InteractionHandlerRef)
		return;

	InteractionHandlerRef->BeginTeleportSelection(this, TileManager->GetTeleporterCoords(), TileManager->TileMap);
}
