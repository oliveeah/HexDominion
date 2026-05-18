#include "DevMode_Widget.h"
#include <Kismet/GameplayStatics.h>
#include "tileSpawningLogic/TileManager.h"
#include "tileSpawningLogic/TileInteractionHandler.h"
#include "tileSpawningLogic/BG_Tile.h"
#include "Occupant/TroopSpawner.h"
#include "Occupant/Occupant_BaseClass.h"
#include "Occupant/Occupant_Troop_BaseClass.h"
#include "Occupant/Occupant_Building_BaseClass.h"
#include "playerData/ResourceManager.h"
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

	if (!ResourceManager)
	{
		for (TActorIterator<AResourceManager> It(GetWorld()); It; ++It)
		{
			ResourceManager = *It;
			UE_LOG(LogTemp, Display, TEXT("ResourceManager found and assigned!"));
			break;
		}
	}

	if (!ResourceManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("ResourceManager not found in level!"));
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

	if (!SelectedTile)
	{
		UE_LOG(LogTemp, Warning, TEXT("No tile selected to spawn building on!"));
		return;
	}

	if (!SelectedTile->GetIsOccupied())
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot spawn building: selected tile has no troop on it!"));
		return;
	}

	if (!turnManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot spawn building: no TurnManager!"));
		return;
	}

	if (!ResourceManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot spawn building: no ResourceManager!"));
		return;
	}

	const EActivePlayerSide ActivePlayer = turnManager->GetActivePlayer();

	// Get or initialise this player's current build cost
	if (!PlayerBuildCosts.Contains(ActivePlayer))
	{
		PlayerBuildCosts.Add(ActivePlayer, BaseBuildingCost);
	}

	const int32 CurrentCost = PlayerBuildCosts[ActivePlayer];

	if (!ResourceManager->SpendBuildingMaterial(ActivePlayer, CurrentCost))
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot spawn building: player %d needs %d building materials but cannot afford it."),
			(int32)ActivePlayer, CurrentCost);
		return;
	}

	// Cost paid — increment for next build
	PlayerBuildCosts[ActivePlayer] = CurrentCost + 1;

	Spawner->SpawnTroop(BuildingToSpawn, SelectedTile);

	// Notify Blueprint to show the production type picker
	AOccupant_Building_BaseClass* PlacedBuilding = SelectedTile->getOccupyingBuilding();
	if (PlacedBuilding)
	{
		OnBuildingPlaced.Broadcast(PlacedBuilding);
	}

	UE_LOG(LogTemp, Display, TEXT("Spawned building for player %d. Cost was %d, next cost will be %d."),
		(int32)ActivePlayer, CurrentCost, PlayerBuildCosts[ActivePlayer]);
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

bool UDevMode_Widget::CanAffordBuilding() const
{
	if (!turnManager || !ResourceManager || !DevTileManager)
		return false;

	// Must have a tile with a troop selected
	UTileInteractionHandler* Interaction = DevTileManager->GetInteractionHandler();
	if (!Interaction)
		return false;

	ABG_Tile* SelectedTile = Interaction->GetSelectedTile();
	if (!SelectedTile || !SelectedTile->GetIsOccupied())
		return false;

	const EActivePlayerSide ActivePlayer = turnManager->GetActivePlayer();

	// Look up what this player's next build would cost
	const int32* CostPtr = PlayerBuildCosts.Find(ActivePlayer);
	const int32  Cost    = CostPtr ? *CostPtr : BaseBuildingCost;

	const FPlayerResources Resources = ResourceManager->GetResources(ActivePlayer);
	return Resources.BuildingMaterials >= Cost;
}
