// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "playerData/InteractionInterface.h"
#include "Components/DecalComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "tileSpawningLogic/TileHighlightState.h"
#include "gameMode/Enum_PlayerSide.h"
#include "BG_Tile.generated.h"

class AOccupant_BaseClass;
class AOccupant_Troop_BaseClass;
class AOccupant_Building_BaseClass;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FOnTileSelected,
	ABG_Tile*, 
	Tile,
	bool,
	isOccupied);


UCLASS()
class PRODUCTIONPROJCURR_API ABG_Tile : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
private:
	bool isPlayingEffect = false;

	UPROPERTY(VisibleAnywhere)
	AOccupant_Troop_BaseClass* occupyingTroopClass;
	UPROPERTY(VisibleAnywhere)

	ETileHighlightState currentHighlightType = ETileHighlightState::None;

	UPROPERTY(EditAnywhere, Category = "Tile Spawn")
	bool bCanSpawnTroopOnTile = true;

	UPROPERTY(EditAnywhere, Category = "Tile Spawn")
	bool bBuildingCanBePlacedOnTile = true;

	UPROPERTY(VisibleAnywhere)
	AOccupant_Building_BaseClass* occupyingBuildingClass;

	bool bHasBuilding = false;

	public:
	// Sets default values for this actor's properties
		ABG_Tile();

		virtual void BeginPlay() override;

		UFUNCTION()
		void OnDebugToggled();

		virtual void ReactToPlayerInteraction_Implementation() override;

		void setSelectedTile();

		UPROPERTY(BlueprintAssignable, Category = "Tile Debug")

		FOnTileSelected OnTileSelectedDelegate;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* tileMesh;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UDecalComponent* decalComponent;

		USceneComponent* sceneComponent;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tile Info")
		FIntPoint gridCoordinates;

		FIntPoint getGridCoordinates() const { return gridCoordinates; }

		void drawDebugPointer(FColor color);

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool isOccupied = false;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile Info")
		bool isSpawnableTile = true;

		void	SetOccupyingTroop(AOccupant_Troop_BaseClass* Troop) { occupyingTroopClass = Troop; }
		AOccupant_Troop_BaseClass* getOccupyingTroop() const { return occupyingTroopClass; }



		void removeOutlineEffect();
		void addOutlineEffect(const FLinearColor& color);

		UPROPERTY()
		UMaterialInstanceDynamic* HexDecalMID;

		bool getIsPlayingEffect() const { return isPlayingEffect; }
		void SetHighlightType(ETileHighlightState newType) { currentHighlightType = newType; }
		ETileHighlightState& getHighlightType() { return currentHighlightType; }

		bool getCanSpawnTroopOnTile() const { return bCanSpawnTroopOnTile; }

		bool getBuildingCanBePlacedOnTile() const { return bBuildingCanBePlacedOnTile; }
		AOccupant_Building_BaseClass* getOccupyingBuilding() const { return occupyingBuildingClass; }
		void SetOccupyingBuilding(AOccupant_Building_BaseClass* Building) { occupyingBuildingClass = Building; }

		bool getHasBuilding() const { return bHasBuilding; }
		void setHasBuilding(bool hasBuilding) { bHasBuilding = hasBuilding; }

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		EActivePlayerSide owningPlayer =  EActivePlayerSide::None;

		UFUNCTION()
		void SetOwningPlayer(EActivePlayerSide newOwner) { owningPlayer = newOwner; }

		EActivePlayerSide GetOccupyingPlayer() const { return owningPlayer; }

		bool GetIsOccupied() const { return isOccupied; }

		UPROPERTY(EditAnywhere, Category = "Tile Visual")
		FName TileHueParameterName = TEXT("TileTint");

		UPROPERTY(EditAnywhere, Category = "Tile Visual")
		float TileHueSaturation = 0.25f;

		UPROPERTY(EditAnywhere, Category = "Tile Visual")
		float TileHueValue = 1.0f;

		UPROPERTY()
		UMaterialInstanceDynamic* TileMeshMID;

		void ApplyHueFromNoise(float NoiseValue);

		UPROPERTY(EditAnywhere, Category = "Tile Visual")
		UMaterialInterface* HighlightMaterial;

		UPROPERTY(EditAnywhere, Category = "Tile Visual")
		FName HighlightColorParameterName = TEXT("DecalTint");
};