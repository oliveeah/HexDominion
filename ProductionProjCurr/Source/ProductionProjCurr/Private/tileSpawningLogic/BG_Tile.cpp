#include "tileSpawningLogic/BG_Tile.h"
#include "Components/StaticMeshComponent.h"
#include "Components/DecalComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include <Kismet/GameplayStatics.h>
#include "Materials/MaterialInstance.h"

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

void ABG_Tile::ReactToPlayerInteraction_Implementation()
{

	setSelectedTile();
}

void ABG_Tile::setSelectedTile()
{
	OnTileSelectedDelegate.Broadcast(this, isOccupied);
}

void ABG_Tile::removeOutlineEffect()
{
	if (isPlayingEffect)
	{
		isPlayingEffect = false;
		decalComponent->SetVisibility(false);
		currentHighlightType = ETileHighlightState::None;
	}
}

void ABG_Tile::addOutlineEffect(const FLinearColor& color)
{
	isPlayingEffect = true;

	if (HexDecalMID)
	{
		HexDecalMID->SetVectorParameterValue(
			TEXT("DecalTint"),
			color);
	}

	decalComponent->SetVisibility(true);
}

void ABG_Tile::ApplyHueFromNoise(float NoiseValue)
{
	if (!bUseHueFromNoise || !TileMeshMID)
		return;

	const float Normalized = (NoiseValue + 1.0f) * 0.5f;
	const float Hue = FMath::Clamp(Normalized, 0.0f, 1.0f);
	const uint8 HueByte = static_cast<uint8>(Hue * 255.0f);

	const uint8 SatByte = static_cast<uint8>(FMath::Clamp(TileHueSaturation, 0.0f, 1.0f) * 255.0f);
	const uint8 ValByte = static_cast<uint8>(FMath::Clamp(TileHueValue, 0.0f, 1.0f) * 255.0f);
	const FLinearColor TileTint = FLinearColor::MakeFromHSV8(HueByte, SatByte, ValByte);
	TileMeshMID->SetVectorParameterValue(TileHueParameterName, TileTint);

	const uint8 FolSatByte = static_cast<uint8>(FMath::Clamp(FoliageHueSaturation, 0.0f, 1.0f) * 255.0f);
	const uint8 FolValByte = static_cast<uint8>(FMath::Clamp(FoliageHueValue, 0.0f, 1.0f) * 255.0f);
	const FLinearColor FoliageTint = FLinearColor::MakeFromHSV8(HueByte, FolSatByte, FolValByte);
	ApplyFoliageHue(FoliageTint);
}
