// Fill out your copyright notice in the Description page of Project Settings.

#include "DevMode_Widget.h"
#include <Kismet/GameplayStatics.h>
#include "tileSpawningLogic/TileManager.h"
#include "tileSpawningLogic/TileInteractionHandler.h"
#include "tileSpawningLogic/BG_Tile.h"
#include "Occupant/TroopSpawner.h"
#include "Occupant/Occupant_BaseClass.h"
#include "Occupant/Occupant_Troop_BaseClass.h"
#include "Occupant/Occupant_Building_BaseClass.h"
#include "Data_PlayerSetUp.h"
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

	CachePlayerNames();

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
	if (UseContext_Button)
	{
		UseContext_Button->OnClicked.AddDynamic(this, &UDevMode_Widget::UseContext_ButtonClicked);
	}
	if (OpenSkillTree_Button)
	{
		OpenSkillTree_Button->OnClicked.AddDynamic(this, &UDevMode_Widget::OpenSkillTree_ButtonClicked);
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
	else
	{
		turnManager->OnTurnChanged.AddUniqueDynamic(this, &UDevMode_Widget::HandleTurnChanged);
		turnManager->OnAllPlayersTakenTurn.AddUniqueDynamic(this, &UDevMode_Widget::HandleAllPlayersTakenTurn);
		turnManager->OnEndPhaseTurn.AddUniqueDynamic(this, &UDevMode_Widget::HandleAllPlayersTakenTurn);
	}
}

void UDevMode_Widget::CachePlayerNames()
{
	PlayerNames.Empty();

	UData_PlayerSetUp* Setup = UData_PlayerSetUp::Get(this);
	if (Setup && Setup->GetActivePlayers().Num() > 0)
	{
		for (const FPlayerEntry& Entry : Setup->GetActivePlayers())
		{
			PlayerNames.Add(Entry.PlayerSide, Entry.PlayerName);
			UE_LOG(LogTemp, Display, TEXT("Cached name: %s for player %d"),
				*Entry.PlayerName, (int32)Entry.PlayerSide);
		}
	}
	else
	{
		// Fallback: default names when launched without Title Screen
		PlayerNames.Add(EActivePlayerSide::PlayerA, TEXT("Player A"));
		PlayerNames.Add(EActivePlayerSide::PlayerB, TEXT("Player B"));
		PlayerNames.Add(EActivePlayerSide::PlayerC, TEXT("Player C"));
		PlayerNames.Add(EActivePlayerSide::PlayerD, TEXT("Player D"));
		UE_LOG(LogTemp, Warning, TEXT("DevMode_Widget: No setup data found - using default player names."));
	}
}

FString UDevMode_Widget::GetCachedPlayerName(EActivePlayerSide Side) const
{
	if (const FString* Name = PlayerNames.Find(Side))
	{
		return *Name;
	}
	return TEXT("Unknown");
}

void UDevMode_Widget::initializeButtonLabels()
{
	TArray<UButton*> Buttons = {
		SpawnTroopAtSelectedTile_Button,
		SpawnBuildingAtSelectedTile_Button,
		PassTurn_Button,
		UseContext_Button,
		OpenSkillTree_Button
	};

	TArray<UTextBlock*> Labels = {
		SpawnTroopAtSelectedTiled_ButtonLabel,
		SpawnBuildingAtSelectedTile_ButtonLabel,
		PassTurn_ButtonLabel,
		UseContext_ButtonLabel,
		OpenSkillTree_ButtonLabel
	};

	TArray<FString> LabelTexts = {
		TEXT("Spawn Troop At Selected Tile"),
		TEXT("Spawn Building At Selected Tile"),
		TEXT("Pass Turn"),
		TEXT("Use Context Action"),
		TEXT("Open Skill Tree")
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
	if (!turnManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("TurnManager not assigned in DevMode_Widget!"));
		return;
	}

	turnManager->PassTurn();
}

void UDevMode_Widget::SpawnTroopAtSelectedTile_ButtonClicked()
{
	if (!DevTileManager)
		return;

	UTileInteractionHandler* Interaction = DevTileManager->GetInteractionHandler();
	ATroopSpawner*           Spawner     = DevTileManager->TroopSpawner;

	if (!Interaction || !Spawner)
		return;

	ABG_Tile* SelectedTile = Interaction->GetSelectedTile();
	if (SelectedTile)
	{
		Spawner->SpawnTroop(TroopToSpawn, SelectedTile);
		UE_LOG(LogTemp, Display, TEXT("Spawned troop at selected tile"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No tile selected to spawn troop on!"));
	}
}

void UDevMode_Widget::SpawnBuildingAtSelectedTile_ButtonClicked()
{
	if (!DevTileManager)
		return;

	UTileInteractionHandler* Interaction = DevTileManager->GetInteractionHandler();
	ATroopSpawner*           Spawner     = DevTileManager->TroopSpawner;

	if (!Interaction || !Spawner)
		return;

	ABG_Tile* SelectedTile = Interaction->GetSelectedTile();
	if (SelectedTile)
	{
		Spawner->SpawnTroop(BuildingToSpawn, SelectedTile);
		UE_LOG(LogTemp, Display, TEXT("Spawned building at selected tile"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No tile selected to spawn building on!"));
	}
}

void UDevMode_Widget::generateButtonLabelText(UTextBlock* buttonLabel, const FString& labelText)
{
	if (buttonLabel)
	{
		buttonLabel->SetText(FText::FromString(labelText));
	}
}

void UDevMode_Widget::HandleTurnChanged(EActivePlayerSide NewActivePlayer)
{
	OnDevTurnChanged.Broadcast(NewActivePlayer);
}

void UDevMode_Widget::UseContext_ButtonClicked()
{
	if (!DevTileManager)
		return;

	UTileInteractionHandler* Interaction = DevTileManager->GetInteractionHandler();
	if (!Interaction)
		return;

	ABG_Tile* SelectedTile = Interaction->GetSelectedTile();
	if (SelectedTile)
	{
		SelectedTile->UseContextAction(DevTileManager);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No tile selected for context action."));
	}
}

void UDevMode_Widget::HandleAllPlayersTakenTurn(int32 CurrentTurn)
{
	OnRoundCompleted(CurrentTurn);
}

void UDevMode_Widget::OpenSkillTree_ButtonClicked()
{
	if (!SkillTreeWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("SkillTreeWidgetClass not assigned in DevMode_Widget!"));
		return;
	}

	if (!SkillTreeWidgetInstance)
	{
		SkillTreeWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), SkillTreeWidgetClass);
	}

	if (SkillTreeWidgetInstance)
	{
		SkillTreeWidgetInstance->AddToViewport();
	}
}
