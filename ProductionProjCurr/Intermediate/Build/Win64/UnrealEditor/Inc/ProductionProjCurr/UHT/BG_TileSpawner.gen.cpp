// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "tileSpawningLogic/BG_TileSpawner.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeBG_TileSpawner() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
ENGINE_API UClass* Z_Construct_UClass_AActor();
PRODUCTIONPROJCURR_API UClass* Z_Construct_UClass_ABG_Tile_NoRegister();
PRODUCTIONPROJCURR_API UClass* Z_Construct_UClass_ABG_TileSpawner();
PRODUCTIONPROJCURR_API UClass* Z_Construct_UClass_ABG_TileSpawner_NoRegister();
PRODUCTIONPROJCURR_API UClass* Z_Construct_UClass_ATileManager_NoRegister();
PRODUCTIONPROJCURR_API UEnum* Z_Construct_UEnum_ProductionProjCurr_EBiomeType();
PRODUCTIONPROJCURR_API UFunction* Z_Construct_UDelegateFunction_ProductionProjCurr_OnGridBuilt__DelegateSignature();
UPackage* Z_Construct_UPackage__Script_ProductionProjCurr();
// ********** End Cross Module References **********************************************************

// ********** Begin Delegate FOnGridBuilt **********************************************************
struct Z_Construct_UDelegateFunction_ProductionProjCurr_OnGridBuilt__DelegateSignature_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_TileSpawner.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_ProductionProjCurr_OnGridBuilt__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_ProductionProjCurr, nullptr, "OnGridBuilt__DelegateSignature", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_ProductionProjCurr_OnGridBuilt__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_ProductionProjCurr_OnGridBuilt__DelegateSignature_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UDelegateFunction_ProductionProjCurr_OnGridBuilt__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_ProductionProjCurr_OnGridBuilt__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnGridBuilt_DelegateWrapper(const FMulticastScriptDelegate& OnGridBuilt)
{
	OnGridBuilt.ProcessMulticastDelegate<UObject>(NULL);
}
// ********** End Delegate FOnGridBuilt ************************************************************

// ********** Begin Enum EBiomeType ****************************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EBiomeType;
static UEnum* EBiomeType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EBiomeType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EBiomeType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_ProductionProjCurr_EBiomeType, (UObject*)Z_Construct_UPackage__Script_ProductionProjCurr(), TEXT("EBiomeType"));
	}
	return Z_Registration_Info_UEnum_EBiomeType.OuterSingleton;
}
template<> PRODUCTIONPROJCURR_API UEnum* StaticEnum<EBiomeType>()
{
	return EBiomeType_StaticEnum();
}
struct Z_Construct_UEnum_ProductionProjCurr_EBiomeType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Delegate declaration for when tiles are spawned\n" },
#endif
		{ "Grassland.Name", "EBiomeType::Grassland" },
		{ "Hill.Name", "EBiomeType::Hill" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_TileSpawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Delegate declaration for when tiles are spawned" },
#endif
		{ "Water.Name", "EBiomeType::Water" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EBiomeType::Water", (int64)EBiomeType::Water },
		{ "EBiomeType::Grassland", (int64)EBiomeType::Grassland },
		{ "EBiomeType::Hill", (int64)EBiomeType::Hill },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_ProductionProjCurr_EBiomeType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_ProductionProjCurr,
	nullptr,
	"EBiomeType",
	"EBiomeType",
	Z_Construct_UEnum_ProductionProjCurr_EBiomeType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_ProductionProjCurr_EBiomeType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_ProductionProjCurr_EBiomeType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_ProductionProjCurr_EBiomeType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_ProductionProjCurr_EBiomeType()
{
	if (!Z_Registration_Info_UEnum_EBiomeType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EBiomeType.InnerSingleton, Z_Construct_UEnum_ProductionProjCurr_EBiomeType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EBiomeType.InnerSingleton;
}
// ********** End Enum EBiomeType ******************************************************************

// ********** Begin Class ABG_TileSpawner **********************************************************
void ABG_TileSpawner::StaticRegisterNativesABG_TileSpawner()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_ABG_TileSpawner;
UClass* ABG_TileSpawner::GetPrivateStaticClass()
{
	using TClass = ABG_TileSpawner;
	if (!Z_Registration_Info_UClass_ABG_TileSpawner.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("BG_TileSpawner"),
			Z_Registration_Info_UClass_ABG_TileSpawner.InnerSingleton,
			StaticRegisterNativesABG_TileSpawner,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_ABG_TileSpawner.InnerSingleton;
}
UClass* Z_Construct_UClass_ABG_TileSpawner_NoRegister()
{
	return ABG_TileSpawner::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ABG_TileSpawner_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "tileSpawningLogic/BG_TileSpawner.h" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_TileSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnGridBuilt_MetaData[] = {
		{ "Category", "Tile Spawner" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_TileSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tileWidth_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Hex | Setup" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Grid Setup\n" },
#endif
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_TileSpawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Grid Setup" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_numberOfColumns_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Hex | Setup" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_TileSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_numberOfRows_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Hex | Setup" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_TileSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_xSpawnOffset_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Hex | Setup" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_TileSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ySpawnOffset_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Hex | Setup" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_TileSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_noiseFrequency_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Hex | Setup" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Noise Settings\n" },
#endif
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_TileSpawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Noise Settings" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TileClass_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Hex | Biomes" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Tile Classes\n" },
#endif
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_TileSpawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Tile Classes" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WaterTiles_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Hex | Biomes" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_TileSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HillTile_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Hex | Biomes" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_TileSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MeadowTiles_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Hex | Biomes" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_TileSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PathTile_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Hex | Biomes" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_TileSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MeadowDefaultTile_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Hex | Biomes" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_TileSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TileManager_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "TileManager" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_TileSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_numberOfPaths_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Hex | Path" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_TileSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_minPathDistance_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Hex | Path" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_TileSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_turnChance_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Hex | Path" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_TileSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_centerBiasStrength_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Hex | Setup" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_TileSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_centerBiasExponent_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Hex | Setup" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_TileSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_foliageSpawnChance_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Hex | Foliage" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_TileSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUseSubdivisionGaps_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Hex | Path" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_TileSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_subdivisionGapWidth_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Hex | Path" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_TileSpawner.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnGridBuilt;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_tileWidth;
	static const UECodeGen_Private::FIntPropertyParams NewProp_numberOfColumns;
	static const UECodeGen_Private::FIntPropertyParams NewProp_numberOfRows;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_xSpawnOffset;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ySpawnOffset;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_noiseFrequency;
	static const UECodeGen_Private::FClassPropertyParams NewProp_TileClass;
	static const UECodeGen_Private::FClassPropertyParams NewProp_WaterTiles_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_WaterTiles;
	static const UECodeGen_Private::FClassPropertyParams NewProp_HillTile;
	static const UECodeGen_Private::FClassPropertyParams NewProp_MeadowTiles_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_MeadowTiles;
	static const UECodeGen_Private::FClassPropertyParams NewProp_PathTile;
	static const UECodeGen_Private::FClassPropertyParams NewProp_MeadowDefaultTile;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TileManager;
	static const UECodeGen_Private::FIntPropertyParams NewProp_numberOfPaths;
	static const UECodeGen_Private::FIntPropertyParams NewProp_minPathDistance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_turnChance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_centerBiasStrength;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_centerBiasExponent;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_foliageSpawnChance;
	static void NewProp_bUseSubdivisionGaps_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseSubdivisionGaps;
	static const UECodeGen_Private::FIntPropertyParams NewProp_subdivisionGapWidth;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ABG_TileSpawner>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_OnGridBuilt = { "OnGridBuilt", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_TileSpawner, OnGridBuilt), Z_Construct_UDelegateFunction_ProductionProjCurr_OnGridBuilt__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnGridBuilt_MetaData), NewProp_OnGridBuilt_MetaData) }; // 4267761514
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_tileWidth = { "tileWidth", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_TileSpawner, tileWidth), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tileWidth_MetaData), NewProp_tileWidth_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_numberOfColumns = { "numberOfColumns", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_TileSpawner, numberOfColumns), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_numberOfColumns_MetaData), NewProp_numberOfColumns_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_numberOfRows = { "numberOfRows", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_TileSpawner, numberOfRows), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_numberOfRows_MetaData), NewProp_numberOfRows_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_xSpawnOffset = { "xSpawnOffset", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_TileSpawner, xSpawnOffset), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_xSpawnOffset_MetaData), NewProp_xSpawnOffset_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_ySpawnOffset = { "ySpawnOffset", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_TileSpawner, ySpawnOffset), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ySpawnOffset_MetaData), NewProp_ySpawnOffset_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_noiseFrequency = { "noiseFrequency", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_TileSpawner, noiseFrequency), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_noiseFrequency_MetaData), NewProp_noiseFrequency_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_TileClass = { "TileClass", nullptr, (EPropertyFlags)0x0044000000010015, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_TileSpawner, TileClass), Z_Construct_UClass_UClass, Z_Construct_UClass_ABG_Tile_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TileClass_MetaData), NewProp_TileClass_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_WaterTiles_Inner = { "WaterTiles", nullptr, (EPropertyFlags)0x0004000000000000, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UClass, Z_Construct_UClass_ABG_Tile_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_WaterTiles = { "WaterTiles", nullptr, (EPropertyFlags)0x0044000000000015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_TileSpawner, WaterTiles), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WaterTiles_MetaData), NewProp_WaterTiles_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_HillTile = { "HillTile", nullptr, (EPropertyFlags)0x0044000000000015, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_TileSpawner, HillTile), Z_Construct_UClass_UClass, Z_Construct_UClass_ABG_Tile_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HillTile_MetaData), NewProp_HillTile_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_MeadowTiles_Inner = { "MeadowTiles", nullptr, (EPropertyFlags)0x0004000000000000, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UClass, Z_Construct_UClass_ABG_Tile_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_MeadowTiles = { "MeadowTiles", nullptr, (EPropertyFlags)0x0044000000000015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_TileSpawner, MeadowTiles), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MeadowTiles_MetaData), NewProp_MeadowTiles_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_PathTile = { "PathTile", nullptr, (EPropertyFlags)0x0044000000000015, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_TileSpawner, PathTile), Z_Construct_UClass_UClass, Z_Construct_UClass_ABG_Tile_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PathTile_MetaData), NewProp_PathTile_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_MeadowDefaultTile = { "MeadowDefaultTile", nullptr, (EPropertyFlags)0x0044000000000015, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_TileSpawner, MeadowDefaultTile), Z_Construct_UClass_UClass, Z_Construct_UClass_ABG_Tile_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MeadowDefaultTile_MetaData), NewProp_MeadowDefaultTile_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_TileManager = { "TileManager", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_TileSpawner, TileManager), Z_Construct_UClass_ATileManager_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TileManager_MetaData), NewProp_TileManager_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_numberOfPaths = { "numberOfPaths", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_TileSpawner, numberOfPaths), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_numberOfPaths_MetaData), NewProp_numberOfPaths_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_minPathDistance = { "minPathDistance", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_TileSpawner, minPathDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_minPathDistance_MetaData), NewProp_minPathDistance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_turnChance = { "turnChance", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_TileSpawner, turnChance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_turnChance_MetaData), NewProp_turnChance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_centerBiasStrength = { "centerBiasStrength", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_TileSpawner, centerBiasStrength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_centerBiasStrength_MetaData), NewProp_centerBiasStrength_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_centerBiasExponent = { "centerBiasExponent", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_TileSpawner, centerBiasExponent), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_centerBiasExponent_MetaData), NewProp_centerBiasExponent_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_foliageSpawnChance = { "foliageSpawnChance", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_TileSpawner, foliageSpawnChance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_foliageSpawnChance_MetaData), NewProp_foliageSpawnChance_MetaData) };
void Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_bUseSubdivisionGaps_SetBit(void* Obj)
{
	((ABG_TileSpawner*)Obj)->bUseSubdivisionGaps = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_bUseSubdivisionGaps = { "bUseSubdivisionGaps", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ABG_TileSpawner), &Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_bUseSubdivisionGaps_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUseSubdivisionGaps_MetaData), NewProp_bUseSubdivisionGaps_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_subdivisionGapWidth = { "subdivisionGapWidth", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_TileSpawner, subdivisionGapWidth), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_subdivisionGapWidth_MetaData), NewProp_subdivisionGapWidth_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ABG_TileSpawner_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_OnGridBuilt,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_tileWidth,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_numberOfColumns,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_numberOfRows,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_xSpawnOffset,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_ySpawnOffset,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_noiseFrequency,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_TileClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_WaterTiles_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_WaterTiles,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_HillTile,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_MeadowTiles_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_MeadowTiles,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_PathTile,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_MeadowDefaultTile,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_TileManager,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_numberOfPaths,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_minPathDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_turnChance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_centerBiasStrength,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_centerBiasExponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_foliageSpawnChance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_bUseSubdivisionGaps,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_subdivisionGapWidth,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ABG_TileSpawner_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ABG_TileSpawner_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_ProductionProjCurr,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ABG_TileSpawner_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ABG_TileSpawner_Statics::ClassParams = {
	&ABG_TileSpawner::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ABG_TileSpawner_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ABG_TileSpawner_Statics::PropPointers),
	0,
	0x009001A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ABG_TileSpawner_Statics::Class_MetaDataParams), Z_Construct_UClass_ABG_TileSpawner_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ABG_TileSpawner()
{
	if (!Z_Registration_Info_UClass_ABG_TileSpawner.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ABG_TileSpawner.OuterSingleton, Z_Construct_UClass_ABG_TileSpawner_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ABG_TileSpawner.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ABG_TileSpawner);
ABG_TileSpawner::~ABG_TileSpawner() {}
// ********** End Class ABG_TileSpawner ************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_tileSpawningLogic_BG_TileSpawner_h__Script_ProductionProjCurr_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EBiomeType_StaticEnum, TEXT("EBiomeType"), &Z_Registration_Info_UEnum_EBiomeType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3239956023U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ABG_TileSpawner, ABG_TileSpawner::StaticClass, TEXT("ABG_TileSpawner"), &Z_Registration_Info_UClass_ABG_TileSpawner, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ABG_TileSpawner), 3979847925U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_tileSpawningLogic_BG_TileSpawner_h__Script_ProductionProjCurr_3816978111(TEXT("/Script/ProductionProjCurr"),
	Z_CompiledInDeferFile_FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_tileSpawningLogic_BG_TileSpawner_h__Script_ProductionProjCurr_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_tileSpawningLogic_BG_TileSpawner_h__Script_ProductionProjCurr_Statics::ClassInfo),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_tileSpawningLogic_BG_TileSpawner_h__Script_ProductionProjCurr_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_tileSpawningLogic_BG_TileSpawner_h__Script_ProductionProjCurr_Statics::EnumInfo));
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
