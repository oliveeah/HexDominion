#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "gameMode/TurnManager.h"
#include "gameMode/Enum_PlayerSide.h"
#include "Occupant/Occupant_Building_BaseClass.h"
#include "Occupant/Occupant_Troop_BaseClass.h"
#include "playerData/ResourceManager.h"
#include "tileSpawningLogic/TileManager.h"
#include "DevMode_Widget.generated.h"

class ATileManager;
class AOccupant_Troop_BaseClass;
class AOccupant_Building_BaseClass;
class AOccupant_BaseClass;
class AResourceManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDevTurnChanged, EActivePlayerSide, NewActivePlayer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingPlaced, AOccupant_Building_BaseClass*, PlacedBuilding);

UCLASS()
class PRODUCTIONPROJCURR_API UDevMode_Widget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	void generateButtonLabelText(UTextBlock* buttonLabel, const FString& labelText);
	void initializeButtonLabels();
	void CachePlayerNames();

	UFUNCTION()
	void SpawnTroopAtSelectedTile_ButtonClicked();

	UFUNCTION()
	void SpawnBuildingAtSelectedTile_ButtonClicked();

	UFUNCTION()
	void PassTurn_ButtonClicked();

	UFUNCTION()
	void HandleTurnChanged(EActivePlayerSide NewActivePlayer);

	UFUNCTION()
	void UseContext_ButtonClicked();

	UFUNCTION()
	void OpenSkillTree_ButtonClicked();

	// Resource / troop info handlers
	UFUNCTION()
	void HandleResourcesChanged(EActivePlayerSide Player, FPlayerResources NewResources);

	UFUNCTION()
	void HandleTroopSelected(AOccupant_Troop_BaseClass* SelectedTroop, int32 Health, int32 MovesRemaining);

	UFUNCTION()
	void HandleTroopDeselected_Internal();

public:
	UPROPERTY(BlueprintAssignable, Category = "TurnManager")
	FOnDevTurnChanged OnDevTurnChanged;

	// Fired after resources are spent — Blueprint shows the picker, then calls ConfirmBuildingSpawn
	UPROPERTY(BlueprintAssignable, Category = "Building")
	FOnBuildingPlaced OnBuildingPlaced;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> SpawnBuildingAtSelectedTile_Button;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> SpawnBuildingAtSelectedTile_ButtonLabel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> SpawnTroopAtSelectedTile_Button;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> SpawnTroopAtSelectedTiled_ButtonLabel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> PassTurn_Button;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> PassTurn_ButtonLabel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> UseContext_Button;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> UseContext_ButtonLabel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> OpenSkillTree_Button;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> OpenSkillTree_ButtonLabel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillTree")
	TSubclassOf<UUserWidget> SkillTreeWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "SkillTree")
	TObjectPtr<UUserWidget> SkillTreeWidgetInstance;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> WidgetTitle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TileManager")
	ATileManager* DevTileManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileManager")
	TSubclassOf<AOccupant_Troop_BaseClass> TroopToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileManager")
	TSubclassOf<AOccupant_Building_BaseClass> BuildingToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TurnManager")
	ATurnManager* turnManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	AResourceManager* ResourceManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	int32 BaseBuildingCost = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerData")
	TMap<EActivePlayerSide, FString> PlayerNames;

	UFUNCTION(BlueprintPure, Category = "PlayerData")
	FString GetCachedPlayerName(EActivePlayerSide Side) const;

	UFUNCTION(BlueprintImplementableEvent, Category = "TurnManager")
	void OnRoundCompleted(int32 CurrentTurn);

	UFUNCTION()
	void HandleAllPlayersTakenTurn(int32 CurrentTurn);

	UFUNCTION(BlueprintCallable, Category = "Animation")
	void SetIsAnimating(bool bAnimating) { bIsAnimating = bAnimating; }

	UFUNCTION(BlueprintPure, Category = "Animation")
	bool GetIsAnimating() const { return bIsAnimating; }

	UFUNCTION(BlueprintCallable, Category = "Building")
	void ConfirmBuildingSpawn(EBuildingProductionType ChosenType);

	UFUNCTION(BlueprintPure, Category = "Building")
	bool CanAffordBuilding() const;

	// Implement in Blueprint to update resource HUD
	UFUNCTION(BlueprintImplementableEvent, Category = "HUD")
	void OnResourcesUpdated(EActivePlayerSide Player, const FPlayerResources& NewResources);

	// Implement in Blueprint to show the troop stat panel
	UFUNCTION(BlueprintImplementableEvent, Category = "HUD")
	void OnTroopInfoUpdated(int32 Health, int32 ActionsRemaining, ETroopType TroopType);

	// Implement in Blueprint to hide the troop stat panel
	UFUNCTION(BlueprintImplementableEvent, Category = "HUD")
	void OnTroopDeselected();

private:
	bool bIsAnimating = false;

	TMap<EActivePlayerSide, int32> PlayerBuildCosts;

	UPROPERTY()
	ABG_Tile* PendingBuildTile = nullptr;

	EActivePlayerSide PendingBuildPlayer = EActivePlayerSide::None;
};
