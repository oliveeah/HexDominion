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

	UFUNCTION()
	void OnNameCommitted(const FText& Text, ETextCommit::Type CommitMethod);

	UFUNCTION()
	void OnStartGameClicked();

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

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEditableTextBox> EditableTextBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> Text_EnterPlayerName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<UButton> StartGame_Button;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<USizeBox> EnterPlayerName_SB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TitleScreen")
	FName GameLevelName = TEXT("GameLevel");

private:
	int32 NumPlayers    = 2;
	int32 CurrentEntry  = 0;        
	TArray<FString> CollectedNames; 
};
