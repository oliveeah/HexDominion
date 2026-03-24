// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Occupant/Occupant_BaseClass.h"
#include "Components/SkeletalMeshComponent.h"
#include "Occupant_Troop_BaseClass.generated.h"

class USkeletalMesh;
class UOccupant_Troop_Data;
class UAnimInstance;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnIsMovingChanged,
	bool,
	NewValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnIsAttackingChanged,
	bool,
	NewValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(
	FOnTroopDeath);

UCLASS()
class PRODUCTIONPROJCURR_API AOccupant_Troop_BaseClass : public AOccupant_BaseClass
{
	GENERATED_BODY()

	private:
		int Damage = 1;

		FVector MoveTarget;

		FName MoveSocketName = TEXT("TroopSpawnSocket");
		
		UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float MoveInterpSpeed = 6.f;

		UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float SnapDistance = 5.f;

		ABG_Tile* TargetTile = nullptr;

		UPROPERTY(VisibleAnywhere, Category = "Animation")
		bool bIsMoving = false;

		UPROPERTY(VisibleAnywhere, Category = "Animation")
		bool bIsAttacking = false;

		UPROPERTY(EditDefaultsOnly, Category = "Components")
		USkeletalMeshComponent* SkeletalMesh;

		UPROPERTY(EditDefaultsOnly, Category = "Team")
		UOccupant_Troop_Data* TroopData;

	public:
		//delegates
		UPROPERTY(BlueprintAssignable, Category = "Events")
		FOnIsMovingChanged OnIsMovingChanged;

		UPROPERTY(BlueprintAssignable, Category = "Events")
		FOnIsAttackingChanged OnIsAttackingChanged;

		UPROPERTY(BlueprintAssignable, Category = "Events")
		FOnTroopDeath OnTroopDeath;





		/*Setters*/ 
		UFUNCTION(BlueprintCallable)
		void SetIsMoving(bool NewIsMoving)
		{
			if (bIsMoving != NewIsMoving)
			{
				bIsMoving = NewIsMoving;
				OnIsMovingChanged.Broadcast(bIsMoving);
			}
		}

		UFUNCTION(BlueprintCallable)
		void SetIsAttacking(bool NewIsAttacking)
		{
			if (bIsAttacking != NewIsAttacking)
			{
				bIsAttacking = NewIsAttacking;
				OnIsAttackingChanged.Broadcast(bIsAttacking);
			}
		}

		void SetHealth(int32 NewHealth) override;
		void SetDamage(int NewDamage);
		void SetOwningPlayer(EActivePlayerSide NewPlayer) override;

		/*Getters*/ 
		bool getIsMoving() const { return bIsMoving; }
		bool getIsAttacking() const { return bIsAttacking; }
		int  GetTroopHealth() const { return Health; }
		int  GetTroopDamage() const { return Damage; }


		/*Movement*/
		virtual bool CanMoveTo(const FIntPoint& Target, TArray<FIntPoint> Neighbors) const;
		virtual void MoveToTile(class ABG_Tile* Tile);

		void TroopDeath()
		{
			this->Destroy();
		}

		/*Overrides*/
		bool		 IsTroop() const override { return true; }

		virtual void Tick(float DeltaTime) override;

		AOccupant_Troop_BaseClass();

		void BeginPlay() override;

	protected:
};
