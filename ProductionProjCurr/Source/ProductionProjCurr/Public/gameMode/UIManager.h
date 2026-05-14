#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "gameMode/Enum_PlayerSide.h"
#include "UIManager.generated.h"

class UUserWidget;
class APlayerController;

UCLASS()
class PRODUCTIONPROJCURR_API UUIManager : public UObject
{
	GENERATED_BODY()
public:
	UUIManager();

	void ShowUIForPlayer(EActivePlayerSide PlayerSide);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UUserWidget* PlayerAWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UUserWidget* PlayerBWidget;
};
