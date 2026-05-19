#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Occupant_Troop_Data.generated.h"

class AOccupant_Troop_BaseClass;

USTRUCT(BlueprintType)
struct FTeamVisualData
{
	GENERATED_BODY()

	// Assign a Blueprint subclass of AOccupant_Troop_BaseClass here.
	// The mesh, anim class, and materials are taken from that Blueprint's defaults.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowedClasses = "Occupant_Troop_BaseClass"))
	TSubclassOf<AOccupant_Troop_BaseClass> TroopBlueprint = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Scale = 1.0f;
};

UCLASS()
class PRODUCTIONPROJCURR_API UOccupant_Troop_Data : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FTeamVisualData FTeamVisualData_PlayerA;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FTeamVisualData FTeamVisualData_PlayerB;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FTeamVisualData FTeamVisualData_PlayerC;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FTeamVisualData FTeamVisualData_PlayerD;
};
