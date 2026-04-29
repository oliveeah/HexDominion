// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h" 
#include "gameMode/Enum_PlayerSide.h"
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

UCLASS()
class PRODUCTIONPROJCURR_API AResourceManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResourceManager();

	    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	TMap<EActivePlayerSide, FPlayerResources> PlayerResources;

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
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	


};
