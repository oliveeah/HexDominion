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
				return FLinearColor(0.002000, 0.010000, 0.030000, 1.000000); 
			case ETileHighlightState::Attack:
				return FLinearColor(2.000000, 0, 0, 1); 
			case ETileHighlightState::Blocked:
				return FLinearColor(5, 5, 5, 1); 
			case ETileHighlightState::Teleporter:
				return FLinearColor(0.002000, 0.010000, 0.030000, 1.000000); 
			default:
				return FLinearColor(5, 5, 5, 1); 
		}
	}

}
