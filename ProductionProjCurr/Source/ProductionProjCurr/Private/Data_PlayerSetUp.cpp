// Fill out your copyright notice in the Description page of Project Settings.


#include "Data_PlayerSetUp.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"

UData_PlayerSetUp* UData_PlayerSetUp::Get(const UObject* WorldContext)
{
	if (!WorldContext)
		return nullptr;

	UGameInstance* GI = UGameplayStatics::GetGameInstance(WorldContext);
	if (!GI)
		return nullptr;

	// Correct subsystem access - no Cast required, type is guaranteed
	return GI->GetSubsystem<UData_PlayerSetUp>();
}

void UData_PlayerSetUp::SetupPlayers(int32 NumPlayers, const TArray<FString>& Names)
{
	Players.Empty();

	const TArray<EActivePlayerSide> Sides = {
		EActivePlayerSide::PlayerA,
		EActivePlayerSide::PlayerB,
		EActivePlayerSide::PlayerC,
		EActivePlayerSide::PlayerD
	};

	NumPlayers = FMath::Clamp(NumPlayers, 2, 4);

	for (int32 i = 0; i < NumPlayers; ++i)
	{
		FPlayerEntry Entry;
		Entry.PlayerSide = Sides[i];
		Entry.bIsActive  = true;
		Entry.PlayerName = Names.IsValidIndex(i)
			? Names[i]
			: FString::Printf(TEXT("Player %d"), i + 1);
		Players.Add(Entry);
	}
}

TArray<FPlayerEntry> UData_PlayerSetUp::GetActivePlayers() const
{
	TArray<FPlayerEntry> Active;
	for (const FPlayerEntry& E : Players)
	{
		if (E.bIsActive)
			Active.Add(E);
	}
	return Active;
}

FString UData_PlayerSetUp::GetPlayerName(EActivePlayerSide Side) const
{
	for (const FPlayerEntry& E : Players)
	{
		if (E.PlayerSide == Side)
			return E.PlayerName;
	}
	return TEXT("Unknown");
}
