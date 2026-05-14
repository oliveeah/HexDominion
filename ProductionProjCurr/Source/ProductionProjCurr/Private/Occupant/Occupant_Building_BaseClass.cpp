#include "Occupant/Occupant_Building_BaseClass.h"

void AOccupant_Building_BaseClass::BeginPlay()
{
	Super::BeginPlay();
}

void AOccupant_Building_BaseClass::SetOwningPlayer(EActivePlayerSide NewPlayer)
{
	Super::SetOwningPlayer(NewPlayer);

	if (!StaticMesh)
		return;

	switch (NewPlayer)
	{
		case EActivePlayerSide::PlayerA:
			if (PlayerAStaticMesh)
			{
				StaticMesh->SetStaticMesh(PlayerAStaticMesh);
			}
			break;
		case EActivePlayerSide::PlayerB:
			if (PlayerBStaticMesh)
			{
				StaticMesh->SetStaticMesh(PlayerBStaticMesh);
			}
			break;
		case EActivePlayerSide::None:
		default:
			break;
	}
}

AOccupant_Building_BaseClass::AOccupant_Building_BaseClass()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComp);
}
