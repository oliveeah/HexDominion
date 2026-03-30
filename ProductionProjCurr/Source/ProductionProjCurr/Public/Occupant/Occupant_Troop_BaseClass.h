// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Occupant/Occupant_BaseClass.h"
#include "Components/SkeletalMeshComponent.h"
#include "Occupant_Troop_BaseClass.generated.h"

class USkeletalMesh;
class UOccupant_Troop_Data;
class UAnimInstance;


UENUM(BlueprintType)
enum class ETroopState : uint8
{
	Idle,
	Moving,
	Attacking,
	Dead
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnStateChanged,
	ETroopState,
	NewState);


UCLASS()
class PRODUCTIONPROJCURR_API AOccupant_Troop_BaseClass : public AOccupant_BaseClass
{
	GENERATED_BODY()

	private:

		UPROPERTY(EditDefaultsOnly, Category = "Animation")
		ETroopState CurrentState = ETroopState::Idle;

		UPROPERTY(EditDefaultsOnly, Category = "Stats")
		int Damage = 1;


		FName MoveSocketName = TEXT("TroopSpawnSocket");
		
		UPROPERTY(EditDefaultsOnly, Category = "Stats | Debug")
		 float MoveInterpSpeed = 6.f;

		UPROPERTY(EditDefaultsOnly, Category = "Stats | Debug")
		 float SnapDistance = 5.f;

		ABG_Tile* TargetTile = nullptr;
		FVector	  MoveTarget;


		UPROPERTY(EditDefaultsOnly, Category = "Components")
		USkeletalMeshComponent* SkeletalMesh;

		UPROPERTY(EditDefaultsOnly, Category = "Team")
		UOccupant_Troop_Data* TroopData;

	public:
		//delegates
		UPROPERTY(BlueprintAssignable, Category = "Events")
		FOnStateChanged OnStateChanged;

		UFUNCTION(BlueprintCallable)
		void SetTroopState(ETroopState NewState);
		void SetHealth(int32 NewHealth) override;
		void SetDamage(int NewDamage);
		void SetOwningPlayer(EActivePlayerSide NewPlayer) override;

		/*Getters*/ 
		int  GetTroopHealth() const { return Health; }
		int  GetTroopDamage() const { return Damage; }
		ETroopState GetTroopState() const { return CurrentState; }

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


