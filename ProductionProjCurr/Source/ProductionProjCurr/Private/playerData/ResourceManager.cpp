#include "playerData/ResourceManager.h"
#include "Data_PlayerSetUp.h"

AResourceManager::AResourceManager()
{
	
	PrimaryActorTick.bCanEverTick = false;

}

void AResourceManager::BeginPlay()
{
	Super::BeginPlay();

	UData_PlayerSetUp* Setup = UData_PlayerSetUp::Get(this);
	if (Setup && Setup->GetActivePlayers().Num() > 0)
	{
		
		for (const FPlayerEntry& Entry : Setup->GetActivePlayers()) 
		{
			PlayerResources.Add(Entry.PlayerSide, FPlayerResources());
		}
		UE_LOG(LogTemp, Display, TEXT("ResourceManager: Initialised %d player resource slots."), PlayerResources.Num());
	}
	else
	{
		
		PlayerResources.Add(EActivePlayerSide::PlayerA, FPlayerResources());
		PlayerResources.Add(EActivePlayerSide::PlayerB, FPlayerResources());
		PlayerResources.Add(EActivePlayerSide::PlayerC, FPlayerResources());
		PlayerResources.Add(EActivePlayerSide::PlayerD, FPlayerResources());
		UE_LOG(LogTemp, Warning, TEXT("ResourceManager: No setup data found � defaulting to 4 player slots."));
	}
}

void AResourceManager::AddBuildingMaterial(EActivePlayerSide Player, int32 BuildingMaterials)
{
	if (FPlayerResources* Resources = PlayerResources.Find(Player))
	{
		Resources->BuildingMaterials += BuildingMaterials;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AddBuildingMaterial: No entry found for player %d � was BeginPlay called?"), (int32)Player);
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
		UE_LOG(LogTemp, Warning, TEXT("AddSkillTreeCurrency: No entry found for player %d � was BeginPlay called?"), (int32)Player);
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
