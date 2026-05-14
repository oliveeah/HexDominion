#pragma once

#include "CoreMinimal.h"
#include "Occupant/Occupant_BaseClass.h"
#include "Components/StaticMeshComponent.h"
#include "Occupant_Building_BaseClass.generated.h"

class UStaticMesh;

UCLASS()
class PRODUCTIONPROJCURR_API AOccupant_Building_BaseClass : public AOccupant_BaseClass
{
	GENERATED_BODY()
	
	private:

	protected:

	public:
		virtual bool IsBuilding() const override { return true; }
		
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* StaticMesh;

		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Team")
		UStaticMesh* PlayerAStaticMesh;

		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Team")
		UStaticMesh* PlayerBStaticMesh;

		void BeginPlay() override;
		void SetOwningPlayer(EActivePlayerSide NewPlayer) override;

		AOccupant_Building_BaseClass();
};
