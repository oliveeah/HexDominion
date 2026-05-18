#pragma once

#include "CoreMinimal.h"
#include "gameMode/Enum_PlayerSide.h"
#include "tileSpawningLogic/TileHighlightState.h"

namespace TileManagerHelper_Functions
{
	inline bool IsFriendlyFire(EActivePlayerSide AttackingPlayerID, EActivePlayerSide TargetPlayerID)
	{
		return AttackingPlayerID == TargetPlayerID;
	}

	inline bool IsEnemyOccupant(EActivePlayerSide TroopToCheck, EActivePlayerSide ActivePlayer)
	{
		return TroopToCheck != ActivePlayer && TroopToCheck != EActivePlayerSide::None;
	}

	inline FLinearColor GetOutlineColor(ETileHighlightState HighlightState)
	{
		switch (HighlightState)
		{
			case ETileHighlightState::Standard:
				return FLinearColor(0, 0, 0, 1);
			case ETileHighlightState::Adjacency:
				return FLinearColor(0.0f, 0.5f, 10.0f, 1.0f);
			case ETileHighlightState::Attack:
				return FLinearColor(2.0f, 0, 0, 1);
			case ETileHighlightState::Blocked:
				return FLinearColor(5, 5, 5, 1);
			case ETileHighlightState::Teleporter:
				return FLinearColor(0.0f, 0.5f, 10.0f, 1.0f);
			case ETileHighlightState::Heal:
				return FLinearColor(0.0f, 8.0f, 0.0f, 1.0f);
			default:
				return FLinearColor(5, 5, 5, 1);
		}
	}
}
