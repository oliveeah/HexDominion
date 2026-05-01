// Fill out your copyright notice in the Description page of Project Settings.


#include "tileSpawningLogic/Tile_Special_Cornucopia.h"

void ATile_Special_Cornucopia::UseContextAction(ATileManager* InTileManager)
{
	UE_LOG(LogTemp, Display, TEXT("Cornucopia context action triggered at (%d, %d)"),
		GetGridCoordinates().X, GetGridCoordinates().Y);
}