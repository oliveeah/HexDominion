// Fill out your copyright notice in the Description page of Project Settings.

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

	// Hand off to the interaction handler to highlight destinations and await selection
	InteractionHandlerRef->BeginTeleportSelection(this, TileManager->GetTeleporterCoords(), TileManager->TileMap);
}
