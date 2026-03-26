// Fill out your copyright notice in the Description page of Project Settings.


#include "BG_Tile.h"
#include <gameMode/ProductionProjCurrGameMode.h>
#include <Kismet/GameplayStatics.h>
#include "Materials/MaterialInstance.h"
#include "TileManager.h" // Only if you need to reference it here


ABG_Tile::ABG_Tile()
{
	PrimaryActorTick.bCanEverTick = false;

	sceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("scene component"));
	SetRootComponent(sceneComponent);

	tileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("tile mesh"));
	tileMesh->SetupAttachment(sceneComponent);

	tileMesh->SetBoundsScale(1000.0f);
	tileMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	tileMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	tileMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	decalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("decal component"));
	decalComponent->SetupAttachment(sceneComponent);

	Tags.Add(FName("Tile"));
}

void ABG_Tile::BeginPlay()
{
	Super::BeginPlay();

	if(AProductionProjCurrGameMode* GameMode = Cast<AProductionProjCurrGameMode>(UGameplayStatics::GetGameMode(this)))	
	{
		GameMode->OnToggleTileDebugCoordinates.AddDynamic(this, &ABG_Tile::OnDebugToggled);
	}

	if (tileMesh && tileMesh->GetMaterial(0))
	{
		TileMeshMID = UMaterialInstanceDynamic::Create(tileMesh->GetMaterial(0), this);
		tileMesh->SetMaterial(0, TileMeshMID);
	}

	if (decalComponent && decalComponent->GetMaterial(0))
	{
		HexDecalMID = UMaterialInstanceDynamic::Create(
			decalComponent->GetMaterial(0), this);

		decalComponent->SetMaterial(0, HexDecalMID);
	}
}

void ABG_Tile::OnDebugToggled()
{

	FString DebugText = FString::Printf(
		TEXT("(%d, %d)"),
		gridCoordinates.X,
		gridCoordinates.Y);

	DrawDebugString(GetWorld(), GetActorLocation() + FVector(0, 0, 100), DebugText, nullptr, FColor::Green, 5.0f, true);

}

void ABG_Tile::ReactToPlayerInteraction_Implementation()
{
//	drawDebugPointer(FColor::Yellow);

	setSelectedTile();
}

void ABG_Tile::setSelectedTile()
{
	OnTileSelectedDelegate.Broadcast(this, isOccupied);
}

void ABG_Tile::drawDebugPointer(FColor color)
{
	FString DebugText = FString::Printf(TEXT("^^^"));
	DrawDebugString(GetWorld(), GetActorLocation() + FVector(0, 0, 200), DebugText, nullptr, color, 5.0f, true);
}

void ABG_Tile::removeOutlineEffect()
{
	if (isPlayingEffect)
	{
		//tileEdgeMesh->SetVisibility(false);
		isPlayingEffect = false;
		decalComponent->SetVisibility(false);
		currentHighlightType = ETileHighlightState::None;
	}
}

void ABG_Tile::addOutlineEffect(const FLinearColor& color)
{
	isPlayingEffect = true;

	if (decalComponent)
	{
		if (HighlightMaterial)
		{
			decalComponent->SetMaterial(0, HighlightMaterial);
			HexDecalMID = UMaterialInstanceDynamic::Create(HighlightMaterial, this);
			decalComponent->SetMaterial(0, HexDecalMID);
		}

		if (HexDecalMID)
		{
			HexDecalMID->SetVectorParameterValue(HighlightColorParameterName, color);
		}

		decalComponent->SetVisibility(true);
	}
}

void ABG_Tile::ApplyHueFromNoise(float NoiseValue)
{
	if (!TileMeshMID)
		return;

	const float Normalized = (NoiseValue + 1.0f) * 0.5f;
	const float Hue = FMath::Clamp(Normalized, 0.0f, 1.0f);

	const uint8 HueByte = static_cast<uint8>(Hue * 255.0f);
	const uint8 SatByte = static_cast<uint8>(FMath::Clamp(TileHueSaturation, 0.0f, 1.0f) * 255.0f);
	const uint8 ValByte = static_cast<uint8>(FMath::Clamp(TileHueValue, 0.0f, 1.0f) * 255.0f);

	const FLinearColor Tint = FLinearColor::MakeFromHSV8(HueByte, SatByte, ValByte);

	TileMeshMID->SetVectorParameterValue(TileHueParameterName, Tint);
}





































