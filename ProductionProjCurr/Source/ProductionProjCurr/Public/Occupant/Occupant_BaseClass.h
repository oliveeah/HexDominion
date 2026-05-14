#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "gameMode/Enum_PlayerSide.h"
#include "Occupant_BaseClass.generated.h"

class AMaterialInstanceDynamic;
class ABG_Tile;

UCLASS()
class PRODUCTIONPROJCURR_API AOccupant_BaseClass : public AActor
{
	GENERATED_BODY()
	
protected:	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* RootComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	int32 Health = 3;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid")
	FIntPoint GridPosition;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Team")
	EActivePlayerSide OwningPlayer = EActivePlayerSide::None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Team")
	FLinearColor TeamColor;

	UPROPERTY()
	UMaterialInstanceDynamic* TeamMID;

	virtual void BeginPlay() override;

public:

	virtual void SetHealth(int32 NewHealth);
	virtual void SetGridPosition(const FIntPoint& NewPos);
	virtual void SetOwningPlayer(EActivePlayerSide NewPlayer);
	virtual void SetTeamColor(const FLinearColor& NewColor);

	virtual int				  GetHealth() const;
	virtual FIntPoint		  GetGridPosition() const;
	virtual EActivePlayerSide GetOwningPlayer() const;
	virtual FLinearColor      GetTeamColor() const;

	virtual bool IsBuilding() const { return false; }
	virtual bool IsTroop() const { return false; }

	AOccupant_BaseClass()
	{
		PrimaryActorTick.bCanEverTick = false;
		RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
		SetRootComponent(RootComp);

	}

};
