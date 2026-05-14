#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

UCLASS()
class PRODUCTIONPROJCURR_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()

private:
	UPROPERTY()
	FString Unique_PlayerName;
	UPROPERTY()
	int32 Unique_PlayerID;

public:
	UPROPERTY()
	int32 PlayerScore;
	UPROPERTY()
	int32 NumberOfResources;

	FString GetPlayerName() const 
	{
		return Unique_PlayerName; 
	}
	int32 GetPlayerID() const
	{
		return Unique_PlayerID;
	}
};
