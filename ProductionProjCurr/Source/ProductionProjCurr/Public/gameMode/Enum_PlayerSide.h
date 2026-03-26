#pragma once
#include "CoreMinimal.h"
#include "Enum_PlayerSide.generated.h"

UENUM(BlueprintType)
enum class EActivePlayerSide : uint8
{
	PlayerA UMETA(DisplayName = "Player A"),
	PlayerB UMETA(DisplayName = "Player B"),
	PlayerC UMETA(DisplayName = "Player C"),
	PlayerD UMETA(DisplayName = "Player D"),
	None	UMETA(DisplayName = "None")
};