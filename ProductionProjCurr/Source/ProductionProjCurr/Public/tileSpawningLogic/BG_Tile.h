// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "playerData/InteractionInterface.h"
#include "tileSpawningLogic/TileHighlightState.h"
#include "gameMode/Enum_PlayerSide.h"
#include "BG_Tile.generated.h"

class UStaticMeshComponent;
class UDecalComponent;
class UMaterialInstanceDynamic;
class USceneComponent;
class ATileManager;

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

	UPROPERTY(VisibleAnywhere, Category = "Tile Properties | Occupants")
	AOccupant_Troop_BaseClass* occupyingTroopClass;

	UPROPERTY(VisibleAnywhere, Category = "Tile Properties | Occupants")
	AOccupant_Building_BaseClass* occupyingBuildingClass;

	UPROPERTY(VisibleAnywhere, Category = "Tile Properties | Occupants")
	bool isOccupied = false;

	UPROPERTY(VisibleAnywhere, Category = "Tile Properties | Occupants")
	bool bHasBuilding = false;

	UPROPERTY(VisibleAnywhere, Category = "Tile Properties | Occupants")
	EActivePlayerSide owningPlayer = EActivePlayerSide::None;

	UPROPERTY(EditAnywhere, Category = "Tile Properties | Spawning")
	bool bCanSpawnTroopOnTile = true;

	UPROPERTY(EditAnywhere, Category = "Tile Properties | Spawning")
	bool bBuildingCanBePlacedOnTile = true;

	UPROPERTY(EditAnywhere, Category = "Tile Properties | Spawning")
	bool isSpawnableTile = true;

	UPROPERTY(EditAnywhere, Category = "Tile Properties | Spawning")
	bool bIsSpecialTile = false;


	UPROPERTY(VisibleAnywhere, Category = "Tile Properties | Visual")
	ETileHighlightState currentHighlightType = ETileHighlightState::None;

	UPROPERTY(EditAnywhere, Category = "Tile Properties | Visual")
	FName TileHueParameterName = TEXT("TileTint");

	UPROPERTY(EditAnywhere, Category = "Tile Properties | Visual")
	float TileHueSaturation = 0.25f;

	UPROPERTY(EditAnywhere, Category = "Tile Properties | Visual")
	float TileHueValue = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Tile Properties | Visual")
	bool bUseHueFromNoise = true;

	UPROPERTY(VisibleAnywhere, Category = "Tile | Info")
	FIntPoint gridCoordinates;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* sceneComponent;


	public:

		ABG_Tile();

		virtual void BeginPlay() override;

		virtual void ReactToPlayerInteraction_Implementation() override;

		void setSelectedTile();

		UPROPERTY(BlueprintAssignable, Category = "Tile Debug")

		FOnTileSelected OnTileSelectedDelegate;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* tileMesh;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UDecalComponent* decalComponent;


		//getters
		FIntPoint GetGridCoordinates() const { return gridCoordinates; }
		AOccupant_Troop_BaseClass* getOccupyingTroop() const { return occupyingTroopClass; }
		bool					   getIsPlayingEffect() const { return isPlayingEffect; }
		bool					   getCanSpawnTroopOnTile() const { return bCanSpawnTroopOnTile; }
		bool					   getHasBuilding() const { return bHasBuilding; }
		bool					   getBuildingCanBePlacedOnTile() const { return bBuildingCanBePlacedOnTile; }
		AOccupant_Building_BaseClass* getOccupyingBuilding() const { return occupyingBuildingClass; }
		bool						  GetIsOccupied() const { return isOccupied; }
		EActivePlayerSide			  GetOccupyingPlayer() const { return owningPlayer; }
		ETileHighlightState&		  getHighlightType() { return currentHighlightType; }
		bool					   getIsSpecialTile() const { return bIsSpecialTile; }
		//getters

		//setters
		void SetOccupyingTroop(AOccupant_Troop_BaseClass* Troop) { occupyingTroopClass = Troop; }
		void SetHighlightType(ETileHighlightState newType) { currentHighlightType = newType; }
		void SetOccupyingBuilding(AOccupant_Building_BaseClass* Building) { occupyingBuildingClass = Building; }
		void SetIsOccupied(bool occupied) { isOccupied = occupied; }
		void setHasBuilding(bool hasBuilding) { bHasBuilding = hasBuilding; }
		void SetGridCoordinates(const FIntPoint& coordinates) { gridCoordinates = coordinates; }
		void SetIsSpecialTile(bool bSpecial) { bIsSpecialTile = bSpecial; }

		UFUNCTION()
		void SetOwningPlayer(EActivePlayerSide newOwner) { owningPlayer = newOwner; }
		//setters

		void removeOutlineEffect();
		void addOutlineEffect(const FLinearColor& color);

		UPROPERTY()
		UMaterialInstanceDynamic* HexDecalMID;

		UPROPERTY()
		UMaterialInstanceDynamic* TileMeshMID;

		void ApplyHueFromNoise(float NoiseValue);

		// Forward declaration so the base signature compiles
		virtual void UseContextAction(ATileManager* InTileManager) {}
};