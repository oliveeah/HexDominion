// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/SizeBox.h"
#include "Widget_TitleScreen.generated.h"

UCLASS()
class PRODUCTIONPROJCURR_API UWidget_TitleScreen : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnLeftArrowClicked();

	UFUNCTION()
	void OnRightArrowClicked();

	UFUNCTION()
	void OnConfirmNumPlayersClicked();

	// Called when the player submits their name and moves to the next
	UFUNCTION()
	void OnNameCommitted(const FText& Text, ETextCommit::Type CommitMethod);

	UFUNCTION()
	void OnStartGameClicked();

	// Updates the prompt text to ask for the current player's name
	void PromptForNextPlayer();

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> Button_PlayerSelect_LeftArrow;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> Button_PlayerSelect_RightArrow;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> Button_PlayerSelect_ConfirmNumPlayers;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> NumPlayers_Text;

	// The single reused name input box
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEditableTextBox> EditableTextBox;

	// Shows instructions e.g. "Enter name for Player 1:"
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> Text_EnterPlayerName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UButton> StartGame_Button;

	// The SizeBox containing the name entry section — hidden until player count confirmed
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<USizeBox> EnterPlayerName_SB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TitleScreen")
	FName GameLevelName = TEXT("GameLevel");

private:
	int32 NumPlayers    = 2;
	int32 CurrentEntry  = 0;        // Which player we are currently naming
	TArray<FString> CollectedNames; // Names gathered so far
};
