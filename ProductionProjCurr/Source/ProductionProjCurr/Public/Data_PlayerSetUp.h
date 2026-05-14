#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "gameMode/Enum_PlayerSide.h"
#include "Data_PlayerSetUp.generated.h"

USTRUCT(BlueprintType)
struct FPlayerEntry
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Player")
	FString PlayerName = TEXT("Player");

	UPROPERTY(BlueprintReadWrite, Category = "Player")
	EActivePlayerSide PlayerSide = EActivePlayerSide::None;

	UPROPERTY(BlueprintReadWrite, Category = "Player")
	bool bIsActive = false;
};

UCLASS()
class PRODUCTIONPROJCURR_API UData_PlayerSetUp : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "PlayerSetup")
	static UData_PlayerSetUp* Get(const UObject* WorldContext);

	UFUNCTION(BlueprintCallable, Category = "PlayerSetup")
	void SetupPlayers(int32 NumPlayers, const TArray<FString>& Names);

	UFUNCTION(BlueprintPure, Category = "PlayerSetup")
	TArray<FPlayerEntry> GetActivePlayers() const;

	UFUNCTION(BlueprintPure, Category = "PlayerSetup")
	FString GetPlayerName(EActivePlayerSide Side) const;

	UPROPERTY(BlueprintReadWrite, Category = "PlayerSetup")
	TArray<FPlayerEntry> Players;
};
