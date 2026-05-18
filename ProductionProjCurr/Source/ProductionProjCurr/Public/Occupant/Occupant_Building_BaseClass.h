#pragma once

#include "CoreMinimal.h"
#include "Occupant/Occupant_BaseClass.h"
#include "Components/StaticMeshComponent.h"
#include "Occupant_Building_BaseClass.generated.h"

class UStaticMesh;

UENUM(BlueprintType)
enum class EBuildingProductionType : uint8
{
	MeleeTroop   UMETA(DisplayName = "Melee Troop Building"),
	RangedTroop  UMETA(DisplayName = "Ranged Troop Building"),
	SupportTroop UMETA(DisplayName = "Support Troop Building")
};

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

		// --- Per-production-type meshes, assign in your Blueprint subclass ---
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Production | Meshes")
		UStaticMesh* MeleeTroopMesh;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Production | Meshes")
		UStaticMesh* RangedTroopMesh;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Production | Meshes")
		UStaticMesh* SupportTroopMesh;

		// Which troop type this building will produce each turn
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Production")
		EBuildingProductionType ProductionType = EBuildingProductionType::MeleeTroop;

		UFUNCTION(BlueprintCallable, Category = "Production")
		void SetProductionType(EBuildingProductionType NewType)
		{
			ProductionType = NewType;
			ApplyProductionMesh();
		}

		// Swaps the visible mesh to match the current ProductionType
		UFUNCTION(BlueprintCallable, Category = "Production")
		void ApplyProductionMesh()
		{
			if (!StaticMesh)
				return;

			UStaticMesh* ChosenMesh = nullptr;

			switch (ProductionType)
			{
				case EBuildingProductionType::MeleeTroop:
					ChosenMesh = MeleeTroopMesh;
					break;
				case EBuildingProductionType::RangedTroop:
					ChosenMesh = RangedTroopMesh;
					break;
				case EBuildingProductionType::SupportTroop:
					ChosenMesh = SupportTroopMesh;
					break;
				default:
					break;
			}

			if (ChosenMesh)
			{
				StaticMesh->SetStaticMesh(ChosenMesh);
			}
		}

		void BeginPlay() override;
		void SetOwningPlayer(EActivePlayerSide NewPlayer) override;

		AOccupant_Building_BaseClass();
};
