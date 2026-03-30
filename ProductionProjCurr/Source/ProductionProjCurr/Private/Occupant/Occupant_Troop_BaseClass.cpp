// Fill out your copyright notice in the Description page of Project Settings.


#include "Occupant/Occupant_Troop_BaseClass.h"
#include "Occupant_Troop_Data.h"
#include "tileSpawningLogic/BG_Tile.h"

void AOccupant_Troop_BaseClass::SetTroopState(ETroopState NewState)
{
	CurrentState = NewState;

	switch (CurrentState)
	{
		case ETroopState::Idle:
			break;
		case ETroopState::Moving:
			break;
		case ETroopState::Attacking:
			break;
		case ETroopState::Dead:
			TroopDeath();
			break;
		default:
			break;
	}
	OnStateChanged.Broadcast(CurrentState);
	if (CurrentState == ETroopState::Attacking)
	{
		SetTroopState(ETroopState::Idle);
	}
}

void AOccupant_Troop_BaseClass::SetHealth(int32 NewHealth)
{
	Health = NewHealth;
	if (Health <= 0)
	{
		SetTroopState(ETroopState::Dead);
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
			TeamData = &TroopData->PlayerA;
			break;
		case EActivePlayerSide::PlayerB:
			TeamData = &TroopData->PlayerB;
			break;
		case EActivePlayerSide::PlayerC:
			TeamData = &TroopData->PlayerC;
			break;
		case EActivePlayerSide::PlayerD:
			TeamData = &TroopData->PlayerD;
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

	FVector ToTarget = MoveTarget - GetActorLocation();
	ToTarget.Z = 0; // Ignore vertical difference for rotation
	if (!ToTarget.IsNearlyZero())
	{
		SetActorRotation(ToTarget.Rotation());
	}

	SetTroopState(ETroopState::Moving);
	SetActorTickEnabled(true);
}
