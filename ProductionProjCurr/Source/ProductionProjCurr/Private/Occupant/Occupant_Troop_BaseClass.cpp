// Fill out your copyright notice in the Description page of Project Settings.


#include "Occupant/Occupant_Troop_BaseClass.h"
#include "Occupant_Troop_Data.h"
#include "SFX_Troop_Data.h"
#include "tileSpawningLogic/BG_Tile.h"
#include "Kismet/GameplayStatics.h"

void AOccupant_Troop_BaseClass::LookAtTarget(const FVector& TargetLocation)
{
	FVector ToTarget = TargetLocation - GetActorLocation();
	ToTarget.Z = 0.0f;

	if (ToTarget.IsNearlyZero())
		return;

	const FRotator YawOnly(0.0f, ToTarget.Rotation().Yaw, 0.0f);

	if (GetRootComponent() && GetRootComponent()->GetAttachParent())
	{
		SetActorRelativeRotation(YawOnly);
	}
	else
	{
		SetActorRotation(YawOnly);
	}
}

void AOccupant_Troop_BaseClass::LookAtTarget(AOccupant_BaseClass* Target)
{
	if (!Target)
		return;

	LookAtTarget(Target->GetActorLocation());
}

void AOccupant_Troop_BaseClass::SetTroopState(ETroopState NewState)
{
	const bool bIsActionState =
		NewState == ETroopState::Moving ||
		NewState == ETroopState::Attacking ||
		NewState == ETroopState::Damage;

	if (animatingAction || CurrentState == NewState)
		return;

	CurrentState = NewState;

	switch (CurrentState)
	{
		case ETroopState::Idle:
			break;
		case ETroopState::Moving:
			break;
		case ETroopState::Attacking:
			TroopAttack();
			break;
		case ETroopState::Dead:
			TroopDeath();
			break;
		case ETroopState::Damage:
			TroopDamage();
			break;
		default:
			break;
	}

	OnStateChanged.Broadcast(CurrentState);
}

void AOccupant_Troop_BaseClass::SetHealth(int32 NewHealth)
{
	Health = NewHealth;
	if (Health <= 0)
	{
		SetTroopState(ETroopState::Dead);
	}
	else
	{
		SetTroopState(ETroopState::Damage);
	}
}

void AOccupant_Troop_BaseClass::SetDamage(int NewDamage)
{
	Damage = NewDamage;
}

void AOccupant_Troop_BaseClass::SetOwningPlayer(EActivePlayerSide NewPlayer)
{
	Super::SetOwningPlayer(NewPlayer);

	if (!SkeletalMesh || !TroopData)
		return;

	const FTeamVisualData* TeamData = nullptr;

	switch (NewPlayer)
	{
		case EActivePlayerSide::PlayerA:
			TeamData = &TroopData->FTeamVisualData_PlayerA;
			break;
		case EActivePlayerSide::PlayerB:
			TeamData = &TroopData->FTeamVisualData_PlayerB;
			break;
		case EActivePlayerSide::PlayerC:
			TeamData = &TroopData->FTeamVisualData_PlayerC;
			break;
		case EActivePlayerSide::PlayerD:
			TeamData = &TroopData->FTeamVisualData_PlayerD;
			break;
		default:
			return;
	}

	if (TeamData->Mesh)
	{
		SkeletalMesh->SetSkeletalMesh(TeamData->Mesh);
	}
	if (TeamData->AnimClass)
	{
		SkeletalMesh->SetAnimInstanceClass(TeamData->AnimClass);
	}
	SkeletalMesh->SetWorldScale3D(FVector(TeamData->Scale));

	// Re-cache SFX now that we know the owner
	SetSoundEffects();
}

void AOccupant_Troop_BaseClass::TroopAttack()
{
	if (InteractingTroop)
	{
		LookAtTarget(InteractingTroop);
		InteractingTroop->SetHealth(InteractingTroop->GetHealth() - Damage);
	}
}

void AOccupant_Troop_BaseClass::TroopDamage()
{
	LookAtTarget(InteractingTroop);
}

void AOccupant_Troop_BaseClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentState == ETroopState::Moving)//moveToTile in world space, attach to new socket
	{
		FVector TargetLocation = MoveTarget;
		FVector CurrentLocation = GetActorLocation();

		FVector NewLocation = FMath::VInterpTo(
			CurrentLocation,
			TargetLocation,
			DeltaTime,
			MoveInterpSpeed);

		SetActorLocation(NewLocation);

		if (FVector::Dist(GetActorLocation(), MoveTarget) < SnapDistance)
		{
			if (!TargetTile)
				return;

			SetTroopState(ETroopState::Idle);
			AttachToComponent(
				TargetTile->tileMesh,
				FAttachmentTransformRules::KeepWorldTransform,
				MoveSocketName);

			SetActorLocation(MoveTarget);
			SetGridPosition(TargetTile->GetGridCoordinates());
			SetOwningTile(TargetTile);
			SetActorTickEnabled(false);
			TargetTile = nullptr;
		}
	}
}

AOccupant_Troop_BaseClass::AOccupant_Troop_BaseClass()
{
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(RootComp);

	SkeletalMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SkeletalMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	SkeletalMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
}

void AOccupant_Troop_BaseClass::BeginPlay()
{
	Super::BeginPlay();

	SetTroopState(ETroopState::Idle);	
}

bool AOccupant_Troop_BaseClass::CanMoveTo(const FIntPoint& Target, TArray<FIntPoint> Neighbors) const
{
	for (int i = 0; i < Neighbors.Num(); i++)
	{
		if (Neighbors[i] == Target)
		{
			return true;
		}
	}
	return false;
}

void AOccupant_Troop_BaseClass::MoveToTile(ABG_Tile* Tile)
{

	if (!Tile || !Tile->tileMesh)
		return;

	TargetTile = Tile;
	this->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	EActivePlayerSide OwnerSide = GetOwningPlayer();

	MoveSocketName = TEXT("TroopSpawnSocket");

	if (OwnerSide == EActivePlayerSide::PlayerA)
	{
		MoveSocketName = TEXT("TroopSpawnSocket_PlayerA");
	}
	else if (OwnerSide == EActivePlayerSide::PlayerB)
	{
		MoveSocketName = TEXT("TroopSpawnSocket_PlayerB");
	}
	else if (OwnerSide == EActivePlayerSide::PlayerC)
	{
		MoveSocketName = TEXT("TroopSpawnSocket_PlayerC");
	}
	else if (OwnerSide == EActivePlayerSide::PlayerD)
	{
		MoveSocketName = TEXT("TroopSpawnSocket_PlayerD");
	}

	MoveTarget = Tile->tileMesh->GetSocketLocation(MoveSocketName);

	LookAtTarget(MoveTarget);
	SetTroopState(ETroopState::Moving);
	SetActorTickEnabled(true);
}

void AOccupant_Troop_BaseClass::TroopDeath()
{
	PlaySoundEffect(CachedDeathSound);

	if (OwningTile)
	{
		OwningTile->SetOccupyingTroop(nullptr);
		OwningTile->SetIsOccupied(false);
		OwningTile->SetOwningPlayer(EActivePlayerSide::None);
		OwningTile->removeOutlineEffect();
		OwningTile->SetHighlightType(ETileHighlightState::None);
		OwningTile = nullptr;
	}

	this->Destroy();
}

void AOccupant_Troop_BaseClass::SetSoundEffects()
{
	if (!TroopSFXData)
		return;

	const FTroopSFX* SFX = nullptr;
	EActivePlayerSide OwnerSide = GetOwningPlayer();

	switch (OwnerSide)
	{
		case EActivePlayerSide::PlayerA:
			SFX = &TroopSFXData->FTroopSFX_PlayerA;
			break;
		case EActivePlayerSide::PlayerB:
			SFX = &TroopSFXData->FTroopSFX_PlayerB;
			break;
		case EActivePlayerSide::PlayerC:
			SFX = &TroopSFXData->FTroopSFX_PlayerC;
			break;
		case EActivePlayerSide::PlayerD:
			SFX = &TroopSFXData->FTroopSFX_PlayerD;
			break;
		default:
			return;
	}

	CachedDeathSound = SFX->DeathSound;
	CachedAttackSound = SFX->AttackSound;
	CachedSpawnSound = SFX->SpawnSound;
	CachedMoveSound = SFX->MoveSound;
}

USoundBase* AOccupant_Troop_BaseClass::GetMoveSound() const
{
	return CachedMoveSound;
}

USoundBase* AOccupant_Troop_BaseClass::GetAttackSound() const
{
	return CachedAttackSound;
}

USoundBase* AOccupant_Troop_BaseClass::GetDamageSound() const
{
	return CachedDeathSound;
}

USoundBase* AOccupant_Troop_BaseClass::GetDeathSound() const
{
	return CachedDeathSound;
}

void AOccupant_Troop_BaseClass::NotifyActionAnimationStarted()
{
	animatingAction = true;
	OnIsAnimatingActionChanged.Broadcast(animatingAction);
}

void AOccupant_Troop_BaseClass::NotifyActionAnimationFinished()
{
	animatingAction = false;
	OnIsAnimatingActionChanged.Broadcast(animatingAction);
}

void AOccupant_Troop_BaseClass::PlaySoundEffect(USoundBase* Sound)
{
	if (!Sound)
		return;

	UGameplayStatics::PlaySoundAtLocation(this, Sound, GetActorLocation());
}

