#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "gameMode/Enum_PlayerSide.h"
#include "Data_PlayerSetUp.h"
#include "ResourceManager.generated.h"

USTRUCT(BlueprintType)
struct FPlayerResources
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	int32 SkillTreeCurrency = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	int32 BuildingMaterials = 0;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnResourcesChanged, EActivePlayerSide, Player, FPlayerResources, NewResources);

UCLASS()
class PRODUCTIONPROJCURR_API AResourceManager : public AActor
{
	GENERATED_BODY()

public:
	AResourceManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	TMap<EActivePlayerSide, FPlayerResources> PlayerResources;

	// Fires every time any player's resources change
	UPROPERTY(BlueprintAssignable, Category = "Resources")
	FOnResourcesChanged OnResourcesChanged;

	UFUNCTION(BlueprintCallable, Category = "Resources")
	void AddBuildingMaterial(EActivePlayerSide Player, int32 BuildingMaterials);

	UFUNCTION(BlueprintCallable, Category = "Resources")
	bool SpendBuildingMaterial(EActivePlayerSide Player, int32 BuildingMaterials);

	UFUNCTION(BlueprintCallable, Category = "Resources")
	void AddSkillTreeCurrency(EActivePlayerSide Player, int32 SkillTreeCurrency);

	UFUNCTION(BlueprintCallable, Category = "Resources")
	bool SpendSkillTreeCurrency(EActivePlayerSide Player, int32 SkillTreeCurrency);

	UFUNCTION(BlueprintPure, Category = "Resources")
	FPlayerResources GetResources(EActivePlayerSide Player) const;

protected:
	virtual void BeginPlay() override;
};
