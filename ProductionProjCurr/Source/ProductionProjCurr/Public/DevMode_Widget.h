// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "gameMode/TurnManager.h"
#include "DevMode_Widget.generated.h"

class ATileManager;
class AOccupant_Troop_BaseClass;
class AOccupant_Building_BaseClass;
class AOccupant_BaseClass;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDevTurnChanged, EActivePlayerSide, NewActivePlayer);

UCLASS()
class PRODUCTIONPROJCURR_API UDevMode_Widget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	void generateButtonLabelText(UTextBlock* buttonLabel, const FString& labelText);
	void initializeButtonLabels();

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

public:
	UPROPERTY(BlueprintAssignable, Category = "TurnManager")
	FOnDevTurnChanged OnDevTurnChanged;

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

	UFUNCTION(BlueprintImplementableEvent, Category = "TurnManager")
	void OnRoundCompleted(int32 CurrentTurn);

	UFUNCTION()
	void HandleAllPlayersTakenTurn(int32 CurrentTurn);

	UFUNCTION(BlueprintCallable, Category = "Animation")
	void SetIsAnimating(bool bAnimating) { bIsAnimating = bAnimating; }

	UFUNCTION(BlueprintPure, Category = "Animation")
	bool GetIsAnimating() const { return bIsAnimating; }

private:
	bool bIsAnimating = false;
};
