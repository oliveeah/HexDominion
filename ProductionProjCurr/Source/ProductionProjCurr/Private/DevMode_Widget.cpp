// Fill out your copyright notice in the Description page of Project Settings.


#include "DevMode_Widget.h"
#include <Kismet/GameplayStatics.h>
#include "tileSpawningLogic/TileManager.h"
#include "Occupant/Occupant_BaseClass.h"
#include "Occupant/Occupant_Troop_BaseClass.h"
#include "Occupant/Occupant_Building_BaseClass.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include <vector>

void UDevMode_Widget::NativeConstruct()
{
	Super::NativeConstruct();

	if (WidgetTitle)
	{
		WidgetTitle->SetText(FText::FromString(TEXT("Developer Widget")));
	}

	initializeButtonLabels();

	if (SpawnTroopAtSelectedTile_Button)
	{
		SpawnTroopAtSelectedTile_Button->OnClicked.AddDynamic(this, &UDevMode_Widget::SpawnTroopAtSelectedTile_ButtonClicked);
	}
	if (SpawnBuildingAtSelectedTile_Button)
	{
		SpawnBuildingAtSelectedTile_Button->OnClicked.AddDynamic(this, &UDevMode_Widget::SpawnBuildingAtSelectedTile_ButtonClicked);
	}
	if (PassTurn_Button)
	{
		PassTurn_Button->OnClicked.AddDynamic(this, &UDevMode_Widget::PassTurn_ButtonClicked);
	}

	for (TActorIterator<ATileManager> It(GetWorld()); It; ++It)
	{
		DevTileManager = *It;
		UE_LOG(LogTemp, Display, TEXT("DevTileManager found and assigned!"));
		break;
	}

	if (!DevTileManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find TileManager in the level!"));
	}

	for (TActorIterator<ATurnManager> It(GetWorld()); It; ++It)
	{
		turnManager = *It;
		UE_LOG(LogTemp, Display, TEXT("TurnManager found and assigned!"));
		break;
	}

	if (!turnManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find TurnManager in the level!"));
	}
}

void UDevMode_Widget::initializeButtonLabels()
{
	TArray<UButton*> Buttons = {
		SpawnTroopAtSelectedTile_Button,
		SpawnBuildingAtSelectedTile_Button,
		PassTurn_Button
	};

	TArray<UTextBlock*> Labels = {
		SpawnTroopAtSelectedTiled_ButtonLabel,
		SpawnBuildingAtSelectedTile_ButtonLabel,
		PassTurn_ButtonLabel
	};

	TArray<FString> LabelTexts = {
		TEXT("Spawn Troop At Selected Tile"),
		TEXT("Spawn Building At Selected Tile"),
		TEXT("Pass Turn")
	};

	for (int32 i = 0; i < Buttons.Num(); ++i)
	{
		if (Buttons[i])
		{
			generateButtonLabelText(Labels[i], LabelTexts[i]);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Button at index %d is not valid!"), i);
		}
	}
}

void UDevMode_Widget::PassTurn_ButtonClicked()
{
	UE_LOG(LogTemp, Display, TEXT("pass turn button clicked"));
	if (!turnManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("TurnManager not assigned in DevMode_Widget!"));
		return;
	}
	turnManager->PassTurn();
}

void UDevMode_Widget::SpawnTroopAtSelectedTile_ButtonClicked()
{
	if (DevTileManager)
	{
		if (DevTileManager->SelectedTile)
		{
			DevTileManager->spawnTroop(TroopToSpawn, DevTileManager->SelectedTile);
			UE_LOG(LogTemp, Display, TEXT("Spawned troop at selected tile"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No tile selected to spawn troop on!"));
		}
	}
}

void UDevMode_Widget::SpawnBuildingAtSelectedTile_ButtonClicked()
{
	if (DevTileManager)
	{
		if (DevTileManager->SelectedTile)
		{
			DevTileManager->spawnTroop(BuildingToSpawn, DevTileManager->SelectedTile);
			UE_LOG(LogTemp, Display, TEXT("Spawned building at selected tile"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No tile selected to spawn building on!"));
		}
	}
}

void UDevMode_Widget::generateButtonLabelText(UTextBlock* buttonLabel, const FString& labelText)
{
	if (buttonLabel)
	{
		buttonLabel->SetText(FText::FromString(labelText));
	}
}

