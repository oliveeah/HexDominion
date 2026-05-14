#include "Widget_TitleScreen.h"
#include "Data_PlayerSetUp.h"
#include "Kismet/GameplayStatics.h"

void UWidget_TitleScreen::NativeConstruct()
{
	Super::NativeConstruct();

	NumPlayers   = 2;
	CurrentEntry = 0;
	CollectedNames.Empty();

	if (NumPlayers_Text)
		NumPlayers_Text->SetText(FText::AsNumber(NumPlayers));

	if (EnterPlayerName_SB)
		EnterPlayerName_SB->SetVisibility(ESlateVisibility::Collapsed);

	if (Button_PlayerSelect_LeftArrow)
		Button_PlayerSelect_LeftArrow->OnClicked.AddDynamic(this, &UWidget_TitleScreen::OnLeftArrowClicked);

	if (Button_PlayerSelect_RightArrow)
		Button_PlayerSelect_RightArrow->OnClicked.AddDynamic(this, &UWidget_TitleScreen::OnRightArrowClicked);

	if (Button_PlayerSelect_ConfirmNumPlayers)
		Button_PlayerSelect_ConfirmNumPlayers->OnClicked.AddDynamic(this, &UWidget_TitleScreen::OnConfirmNumPlayersClicked);

	if (EditableTextBox)
		EditableTextBox->OnTextCommitted.AddDynamic(this, &UWidget_TitleScreen::OnNameCommitted);

	if (StartGame_Button)
		StartGame_Button->OnClicked.AddDynamic(this, &UWidget_TitleScreen::OnStartGameClicked);
}

void UWidget_TitleScreen::OnLeftArrowClicked()
{
	NumPlayers = FMath::Clamp(NumPlayers - 1, 2, 4);
	if (NumPlayers_Text)
		NumPlayers_Text->SetText(FText::AsNumber(NumPlayers));
}

void UWidget_TitleScreen::OnRightArrowClicked()
{
	NumPlayers = FMath::Clamp(NumPlayers + 1, 2, 4);
	if (NumPlayers_Text)
		NumPlayers_Text->SetText(FText::AsNumber(NumPlayers));
}

void UWidget_TitleScreen::OnConfirmNumPlayersClicked()
{
	
	CurrentEntry = 0;
	CollectedNames.Empty();

	if (EnterPlayerName_SB)
		EnterPlayerName_SB->SetVisibility(ESlateVisibility::Visible);

	PromptForNextPlayer();
}

void UWidget_TitleScreen::PromptForNextPlayer()
{
	if (Text_EnterPlayerName)
	{
		FString Prompt = FString::Printf(TEXT("Enter name for Player %d:"), CurrentEntry + 1);
		Text_EnterPlayerName->SetText(FText::FromString(Prompt));
	}

	if (EditableTextBox)
	{
		EditableTextBox->SetText(FText::GetEmpty());
		EditableTextBox->SetKeyboardFocus();
	}
}

void UWidget_TitleScreen::OnNameCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	
	if (CommitMethod != ETextCommit::OnEnter && CommitMethod != ETextCommit::OnUserMovedFocus)
		return;

	FString Name = Text.ToString().TrimStartAndEnd();
	if (Name.IsEmpty())
		Name = FString::Printf(TEXT("Player %d"), CurrentEntry + 1);

	CollectedNames.Add(Name);
	CurrentEntry++;

	if (CurrentEntry < NumPlayers)
	{
		
		PromptForNextPlayer();
	}
	else
	{
		
		if (EnterPlayerName_SB)
			EnterPlayerName_SB->SetVisibility(ESlateVisibility::Collapsed);

		if (StartGame_Button)
			StartGame_Button->SetVisibility(ESlateVisibility::Visible);

		UE_LOG(LogTemp, Display, TEXT("All %d player names collected."), NumPlayers);
	}

	for (FString& name : CollectedNames)
	{
		UE_LOG(LogTemp, Display, TEXT("Player Name: %s"), *name);
	}
}

void UWidget_TitleScreen::OnStartGameClicked()
{
	UData_PlayerSetUp* Setup = UData_PlayerSetUp::Get(this);
	if (Setup)
		Setup->SetupPlayers(NumPlayers, CollectedNames);

	UGameplayStatics::OpenLevel(this, GameLevelName);
}
