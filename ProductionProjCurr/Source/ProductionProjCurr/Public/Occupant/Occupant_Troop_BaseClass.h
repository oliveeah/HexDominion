#pragma once

#include "CoreMinimal.h"
#include "Occupant/Occupant_BaseClass.h"
#include "Components/SkeletalMeshComponent.h"
#include "Sound/SoundBase.h"
#include "Occupant_Troop_BaseClass.generated.h"

class USkeletalMesh;
class AOccupant_BaseClass;
class UOccupant_Troop_Data;
class UAnimInstance;
class ABG_Tile;
class USFX_Troop_Data;

UENUM(BlueprintType)
enum class ETroopState : uint8
{
	Idle,
	Moving,
	Attacking,
	Damage,
	Dead
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnStateChanged,
	ETroopState,
	NewState);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnIsAnimatingActionChanged,
	bool,
	bIsAnimatingAction);

UCLASS()
class PRODUCTIONPROJCURR_API AOccupant_Troop_BaseClass : public AOccupant_BaseClass
{
	GENERATED_BODY()

	private:

		UPROPERTY()
		AOccupant_BaseClass* InteractingTroop = nullptr;

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

		FVector MoveTarget;

		UPROPERTY(EditDefaultsOnly, Category = "Components")
		USkeletalMeshComponent* SkeletalMesh;

		UPROPERTY(EditDefaultsOnly, Category = "Team")
		UOccupant_Troop_Data* TroopData;

		UPROPERTY(EditDefaultsOnly, Category = "SFX")
		USFX_Troop_Data* TroopSFXData;

		UPROPERTY()
		ABG_Tile* OwningTile = nullptr;

		void LookAtTarget(const FVector& TargetLocation);
		void LookAtTarget(AOccupant_BaseClass* Target);

	public:
		UPROPERTY(VisibleAnywhere, Category = "DEBUG")
		bool animatingAction = false;

		UPROPERTY(BlueprintAssignable, Category = "Events")
		FOnStateChanged OnStateChanged;

		UPROPERTY(BlueprintAssignable, Category = "Events")
		FOnIsAnimatingActionChanged OnIsAnimatingActionChanged;

		UFUNCTION(BlueprintCallable)
		void SetTroopState(ETroopState NewState);
		void SetHealth(int32 NewHealth) override;
		void SetDamage(int NewDamage);
		void SetOwningPlayer(EActivePlayerSide NewPlayer) override;
		void SetInteractingTroop(AOccupant_BaseClass* NewTarget) { InteractingTroop = NewTarget; }
		void SetOwningTile(ABG_Tile* NewTile) { OwningTile = NewTile; }
		void SetSoundEffects();

		UFUNCTION(BlueprintCallable, Category = "Troop|Animation")
		void NotifyActionAnimationStarted();

		UFUNCTION(BlueprintCallable, Category = "Troop|Animation")
		void NotifyActionAnimationFinished();

		int  GetTroopHealth() const { return Health; }
		int  GetTroopDamage() const { return Damage; }
		ETroopState GetTroopState() const { return CurrentState; }
		ABG_Tile* GetOwningTile() const { return OwningTile; }
		USoundBase* GetMoveSound() const;
		USoundBase* GetAttackSound() const;
		USoundBase* GetDamageSound() const;
		USoundBase* GetDeathSound() const;

		virtual bool CanMoveTo(const FIntPoint& Target, TArray<FIntPoint> Neighbors) const;
		virtual void MoveToTile(class ABG_Tile* Tile);
		virtual void TeleportToTile(class ABG_Tile* Tile);

		void TroopDeath();
		void TroopAttack();
		void TroopDamage();

		bool IsTroop() const override { return true; }

		virtual void Tick(float DeltaTime) override;

		AOccupant_Troop_BaseClass();

		void BeginPlay() override;

		bool TroopAnimatingAction() const { return animatingAction; }

		void PlaySoundEffect(USoundBase* Sound);

	protected:
		UPROPERTY()
		USoundBase* CachedDeathSound = nullptr;

		UPROPERTY()
		USoundBase* CachedAttackSound = nullptr;

		UPROPERTY()
		USoundBase* CachedSpawnSound = nullptr;

		UPROPERTY()
		USoundBase* CachedMoveSound = nullptr;
};
