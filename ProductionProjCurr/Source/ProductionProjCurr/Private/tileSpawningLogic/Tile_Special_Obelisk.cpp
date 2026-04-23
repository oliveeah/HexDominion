// Fill out your copyright notice in the Description page of Project Settings.


#include "tileSpawningLogic/Tile_Special_Obelisk.h"

void ATile_Special_Obelisk::UseContextAction(ATileManager* InTileManager)
{
	UE_LOG(LogTemp, Display, TEXT("Obelisk context action triggered at (%d, %d)"),
		GetGridCoordinates().X, GetGridCoordinates().Y);
}