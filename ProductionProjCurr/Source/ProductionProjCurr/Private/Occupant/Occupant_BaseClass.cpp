#include "Occupant/Occupant_BaseClass.h"
#include "CoreMinimal.h"

void AOccupant_BaseClass::BeginPlay()
{
	Super::BeginPlay();

	SetOwningPlayer(OwningPlayer);

	if (OwningPlayer == EActivePlayerSide::None)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s has OwningPlayer = None"), *GetName());
	}
}

void AOccupant_BaseClass::SetHealth(int32 NewHealth)
{
	Health = NewHealth;
}

void AOccupant_BaseClass::SetGridPosition(const FIntPoint& NewPos)
{
	GridPosition = NewPos;
}

void AOccupant_BaseClass::SetOwningPlayer(EActivePlayerSide NewPlayer)
{
	OwningPlayer = NewPlayer;
}

void AOccupant_BaseClass::SetTeamColor(const FLinearColor& NewColor)
{
	TeamColor = NewColor;

	if (TeamMID)
	{
		TeamMID->SetVectorParameterValue(TEXT("TeamColor"), NewColor);
	}
}

int32 AOccupant_BaseClass::GetHealth() const
{
	return Health;
}

FIntPoint AOccupant_BaseClass::GetGridPosition() const
{
	return GridPosition;
}

EActivePlayerSide AOccupant_BaseClass::GetOwningPlayer() const
{
	return OwningPlayer;
}

FLinearColor AOccupant_BaseClass::GetTeamColor() const
{
	return TeamColor;
}
