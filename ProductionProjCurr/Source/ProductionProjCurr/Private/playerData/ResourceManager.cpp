// Fill out your copyright notice in the Description page of Project Settings.


#include "playerData/ResourceManager.h"

// Sets default values
AResourceManager::AResourceManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AResourceManager::AddBuildingMaterial(EActivePlayerSide Player, int32 BuildingMaterials)
{
	if (FPlayerResources* Resources = PlayerResources.Find(Player))
	{
		Resources->BuildingMaterials += BuildingMaterials;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AddBuildingMaterial: No entry found for player %d — was BeginPlay called?"), (int32)Player);
	}
}

bool AResourceManager::SpendBuildingMaterial(EActivePlayerSide Player, int32 BuildingMaterials)
{
	if (FPlayerResources* Resources = PlayerResources.Find(Player))
	{
		if (Resources->BuildingMaterials >= BuildingMaterials)
		{
			Resources->BuildingMaterials -= BuildingMaterials;
			return true;
		}
	}
	return false;
}

void AResourceManager::AddSkillTreeCurrency(EActivePlayerSide Player, int32 SkillTreeCurrency)
{
	if (FPlayerResources* Resources = PlayerResources.Find(Player))
	{
		Resources->SkillTreeCurrency += SkillTreeCurrency;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AddSkillTreeCurrency: No entry found for player %d — was BeginPlay called?"), (int32)Player);
	}
}

bool AResourceManager::SpendSkillTreeCurrency(EActivePlayerSide Player, int32 SkillTreeCurrency)
{
	if (FPlayerResources* Resources = PlayerResources.Find(Player))
	{
		if (Resources->SkillTreeCurrency >= SkillTreeCurrency)
		{
			Resources->SkillTreeCurrency -= SkillTreeCurrency;
			return true;
		}
	}
	return false;
}

FPlayerResources AResourceManager::GetResources(EActivePlayerSide Player) const
{
	if (const FPlayerResources* Resources = PlayerResources.Find(Player))
	{
		return *Resources;
	}
	return FPlayerResources();
}

// Called when the game starts or when spawned
void AResourceManager::BeginPlay()
{
	Super::BeginPlay();

	PlayerResources.Add(EActivePlayerSide::PlayerA, FPlayerResources());
	PlayerResources.Add(EActivePlayerSide::PlayerB, FPlayerResources());
	PlayerResources.Add(EActivePlayerSide::PlayerC, FPlayerResources());
	PlayerResources.Add(EActivePlayerSide::PlayerD, FPlayerResources());

	UE_LOG(LogTemp, Display, TEXT("ResourceManager: PlayerResources initialized for all 4 players."));
}




