// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "tileSpawningLogic/BG_Tile.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeBG_Tile() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FIntPoint();
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_UDecalComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UMaterialInstanceDynamic_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
PRODUCTIONPROJCURR_API UClass* Z_Construct_UClass_ABG_Tile();
PRODUCTIONPROJCURR_API UClass* Z_Construct_UClass_ABG_Tile_NoRegister();
PRODUCTIONPROJCURR_API UClass* Z_Construct_UClass_AOccupant_Building_BaseClass_NoRegister();
PRODUCTIONPROJCURR_API UClass* Z_Construct_UClass_AOccupant_Troop_BaseClass_NoRegister();
PRODUCTIONPROJCURR_API UClass* Z_Construct_UClass_UInteractionInterface_NoRegister();
PRODUCTIONPROJCURR_API UEnum* Z_Construct_UEnum_ProductionProjCurr_EActivePlayerSide();
PRODUCTIONPROJCURR_API UEnum* Z_Construct_UEnum_ProductionProjCurr_ETileHighlightState();
PRODUCTIONPROJCURR_API UFunction* Z_Construct_UDelegateFunction_ProductionProjCurr_OnTileSelected__DelegateSignature();
UPackage* Z_Construct_UPackage__Script_ProductionProjCurr();
// ********** End Cross Module References **********************************************************

// ********** Begin Delegate FOnTileSelected *******************************************************
struct Z_Construct_UDelegateFunction_ProductionProjCurr_OnTileSelected__DelegateSignature_Statics
{
	struct _Script_ProductionProjCurr_eventOnTileSelected_Parms
	{
		ABG_Tile* Tile;
		bool isOccupied;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_Tile.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Tile;
	static void NewProp_isOccupied_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_isOccupied;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UDelegateFunction_ProductionProjCurr_OnTileSelected__DelegateSignature_Statics::NewProp_Tile = { "Tile", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_ProductionProjCurr_eventOnTileSelected_Parms, Tile), Z_Construct_UClass_ABG_Tile_NoRegister, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UDelegateFunction_ProductionProjCurr_OnTileSelected__DelegateSignature_Statics::NewProp_isOccupied_SetBit(void* Obj)
{
	((_Script_ProductionProjCurr_eventOnTileSelected_Parms*)Obj)->isOccupied = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UDelegateFunction_ProductionProjCurr_OnTileSelected__DelegateSignature_Statics::NewProp_isOccupied = { "isOccupied", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(_Script_ProductionProjCurr_eventOnTileSelected_Parms), &Z_Construct_UDelegateFunction_ProductionProjCurr_OnTileSelected__DelegateSignature_Statics::NewProp_isOccupied_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_ProductionProjCurr_OnTileSelected__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_ProductionProjCurr_OnTileSelected__DelegateSignature_Statics::NewProp_Tile,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_ProductionProjCurr_OnTileSelected__DelegateSignature_Statics::NewProp_isOccupied,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_ProductionProjCurr_OnTileSelected__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_ProductionProjCurr_OnTileSelected__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_ProductionProjCurr, nullptr, "OnTileSelected__DelegateSignature", Z_Construct_UDelegateFunction_ProductionProjCurr_OnTileSelected__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_ProductionProjCurr_OnTileSelected__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_ProductionProjCurr_OnTileSelected__DelegateSignature_Statics::_Script_ProductionProjCurr_eventOnTileSelected_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_ProductionProjCurr_OnTileSelected__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_ProductionProjCurr_OnTileSelected__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_ProductionProjCurr_OnTileSelected__DelegateSignature_Statics::_Script_ProductionProjCurr_eventOnTileSelected_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_ProductionProjCurr_OnTileSelected__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_ProductionProjCurr_OnTileSelected__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnTileSelected_DelegateWrapper(const FMulticastScriptDelegate& OnTileSelected, ABG_Tile* Tile, bool isOccupied)
{
	struct _Script_ProductionProjCurr_eventOnTileSelected_Parms
	{
		ABG_Tile* Tile;
		bool isOccupied;
	};
	_Script_ProductionProjCurr_eventOnTileSelected_Parms Parms;
	Parms.Tile=Tile;
	Parms.isOccupied=isOccupied ? true : false;
	OnTileSelected.ProcessMulticastDelegate<UObject>(&Parms);
}
// ********** End Delegate FOnTileSelected *********************************************************

// ********** Begin Class ABG_Tile Function OnDebugToggled *****************************************
struct Z_Construct_UFunction_ABG_Tile_OnDebugToggled_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_Tile.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ABG_Tile_OnDebugToggled_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ABG_Tile, nullptr, "OnDebugToggled", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ABG_Tile_OnDebugToggled_Statics::Function_MetaDataParams), Z_Construct_UFunction_ABG_Tile_OnDebugToggled_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ABG_Tile_OnDebugToggled()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ABG_Tile_OnDebugToggled_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ABG_Tile::execOnDebugToggled)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnDebugToggled();
	P_NATIVE_END;
}
// ********** End Class ABG_Tile Function OnDebugToggled *******************************************

// ********** Begin Class ABG_Tile Function SetOwningPlayer ****************************************
struct Z_Construct_UFunction_ABG_Tile_SetOwningPlayer_Statics
{
	struct BG_Tile_eventSetOwningPlayer_Parms
	{
		EActivePlayerSide newOwner;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_Tile.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_newOwner_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_newOwner;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_ABG_Tile_SetOwningPlayer_Statics::NewProp_newOwner_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_ABG_Tile_SetOwningPlayer_Statics::NewProp_newOwner = { "newOwner", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BG_Tile_eventSetOwningPlayer_Parms, newOwner), Z_Construct_UEnum_ProductionProjCurr_EActivePlayerSide, METADATA_PARAMS(0, nullptr) }; // 285499111
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ABG_Tile_SetOwningPlayer_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ABG_Tile_SetOwningPlayer_Statics::NewProp_newOwner_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ABG_Tile_SetOwningPlayer_Statics::NewProp_newOwner,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ABG_Tile_SetOwningPlayer_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ABG_Tile_SetOwningPlayer_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ABG_Tile, nullptr, "SetOwningPlayer", Z_Construct_UFunction_ABG_Tile_SetOwningPlayer_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ABG_Tile_SetOwningPlayer_Statics::PropPointers), sizeof(Z_Construct_UFunction_ABG_Tile_SetOwningPlayer_Statics::BG_Tile_eventSetOwningPlayer_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ABG_Tile_SetOwningPlayer_Statics::Function_MetaDataParams), Z_Construct_UFunction_ABG_Tile_SetOwningPlayer_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ABG_Tile_SetOwningPlayer_Statics::BG_Tile_eventSetOwningPlayer_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ABG_Tile_SetOwningPlayer()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ABG_Tile_SetOwningPlayer_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ABG_Tile::execSetOwningPlayer)
{
	P_GET_ENUM(EActivePlayerSide,Z_Param_newOwner);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetOwningPlayer(EActivePlayerSide(Z_Param_newOwner));
	P_NATIVE_END;
}
// ********** End Class ABG_Tile Function SetOwningPlayer ******************************************

// ********** Begin Class ABG_Tile *****************************************************************
void ABG_Tile::StaticRegisterNativesABG_Tile()
{
	UClass* Class = ABG_Tile::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "OnDebugToggled", &ABG_Tile::execOnDebugToggled },
		{ "SetOwningPlayer", &ABG_Tile::execSetOwningPlayer },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_ABG_Tile;
UClass* ABG_Tile::GetPrivateStaticClass()
{
	using TClass = ABG_Tile;
	if (!Z_Registration_Info_UClass_ABG_Tile.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("BG_Tile"),
			Z_Registration_Info_UClass_ABG_Tile.InnerSingleton,
			StaticRegisterNativesABG_Tile,
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
	return Z_Registration_Info_UClass_ABG_Tile.InnerSingleton;
}
UClass* Z_Construct_UClass_ABG_Tile_NoRegister()
{
	return ABG_Tile::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ABG_Tile_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "tileSpawningLogic/BG_Tile.h" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_Tile.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_occupyingTroopClass_MetaData[] = {
		{ "Category", "BG_Tile" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_Tile.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_currentHighlightType_MetaData[] = {
		{ "Category", "BG_Tile" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_Tile.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bCanSpawnTroopOnTile_MetaData[] = {
		{ "Category", "Tile Spawn" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_Tile.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bBuildingCanBePlacedOnTile_MetaData[] = {
		{ "Category", "Tile Spawn" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_Tile.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_occupyingBuildingClass_MetaData[] = {
		{ "Category", "BG_Tile" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_Tile.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnTileSelectedDelegate_MetaData[] = {
		{ "Category", "Tile Debug" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_Tile.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tileMesh_MetaData[] = {
		{ "Category", "Components" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_Tile.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_decalComponent_MetaData[] = {
		{ "Category", "Components" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_Tile.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_gridCoordinates_MetaData[] = {
		{ "Category", "Tile Info" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_Tile.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_isOccupied_MetaData[] = {
		{ "Category", "BG_Tile" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_Tile.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_isSpawnableTile_MetaData[] = {
		{ "Category", "Tile Info" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_Tile.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HexDecalMID_MetaData[] = {
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_Tile.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_owningPlayer_MetaData[] = {
		{ "Category", "BG_Tile" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_Tile.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TileHueParameterName_MetaData[] = {
		{ "Category", "Tile Visual" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_Tile.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TileHueSaturation_MetaData[] = {
		{ "Category", "Tile Visual" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_Tile.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TileHueValue_MetaData[] = {
		{ "Category", "Tile Visual" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_Tile.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TileMeshMID_MetaData[] = {
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_Tile.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_occupyingTroopClass;
	static const UECodeGen_Private::FBytePropertyParams NewProp_currentHighlightType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_currentHighlightType;
	static void NewProp_bCanSpawnTroopOnTile_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bCanSpawnTroopOnTile;
	static void NewProp_bBuildingCanBePlacedOnTile_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bBuildingCanBePlacedOnTile;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_occupyingBuildingClass;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnTileSelectedDelegate;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_tileMesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_decalComponent;
	static const UECodeGen_Private::FStructPropertyParams NewProp_gridCoordinates;
	static void NewProp_isOccupied_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_isOccupied;
	static void NewProp_isSpawnableTile_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_isSpawnableTile;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HexDecalMID;
	static const UECodeGen_Private::FBytePropertyParams NewProp_owningPlayer_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_owningPlayer;
	static const UECodeGen_Private::FNamePropertyParams NewProp_TileHueParameterName;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TileHueSaturation;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TileHueValue;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TileMeshMID;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ABG_Tile_OnDebugToggled, "OnDebugToggled" }, // 3843552734
		{ &Z_Construct_UFunction_ABG_Tile_SetOwningPlayer, "SetOwningPlayer" }, // 648653819
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static const UECodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ABG_Tile>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ABG_Tile_Statics::NewProp_occupyingTroopClass = { "occupyingTroopClass", nullptr, (EPropertyFlags)0x0040000000020001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_Tile, occupyingTroopClass), Z_Construct_UClass_AOccupant_Troop_BaseClass_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_occupyingTroopClass_MetaData), NewProp_occupyingTroopClass_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_ABG_Tile_Statics::NewProp_currentHighlightType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_ABG_Tile_Statics::NewProp_currentHighlightType = { "currentHighlightType", nullptr, (EPropertyFlags)0x0040000000020001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_Tile, currentHighlightType), Z_Construct_UEnum_ProductionProjCurr_ETileHighlightState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_currentHighlightType_MetaData), NewProp_currentHighlightType_MetaData) }; // 1313919674
void Z_Construct_UClass_ABG_Tile_Statics::NewProp_bCanSpawnTroopOnTile_SetBit(void* Obj)
{
	((ABG_Tile*)Obj)->bCanSpawnTroopOnTile = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ABG_Tile_Statics::NewProp_bCanSpawnTroopOnTile = { "bCanSpawnTroopOnTile", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ABG_Tile), &Z_Construct_UClass_ABG_Tile_Statics::NewProp_bCanSpawnTroopOnTile_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bCanSpawnTroopOnTile_MetaData), NewProp_bCanSpawnTroopOnTile_MetaData) };
void Z_Construct_UClass_ABG_Tile_Statics::NewProp_bBuildingCanBePlacedOnTile_SetBit(void* Obj)
{
	((ABG_Tile*)Obj)->bBuildingCanBePlacedOnTile = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ABG_Tile_Statics::NewProp_bBuildingCanBePlacedOnTile = { "bBuildingCanBePlacedOnTile", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ABG_Tile), &Z_Construct_UClass_ABG_Tile_Statics::NewProp_bBuildingCanBePlacedOnTile_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bBuildingCanBePlacedOnTile_MetaData), NewProp_bBuildingCanBePlacedOnTile_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ABG_Tile_Statics::NewProp_occupyingBuildingClass = { "occupyingBuildingClass", nullptr, (EPropertyFlags)0x0040000000020001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_Tile, occupyingBuildingClass), Z_Construct_UClass_AOccupant_Building_BaseClass_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_occupyingBuildingClass_MetaData), NewProp_occupyingBuildingClass_MetaData) };
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_ABG_Tile_Statics::NewProp_OnTileSelectedDelegate = { "OnTileSelectedDelegate", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_Tile, OnTileSelectedDelegate), Z_Construct_UDelegateFunction_ProductionProjCurr_OnTileSelected__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnTileSelectedDelegate_MetaData), NewProp_OnTileSelectedDelegate_MetaData) }; // 2066019166
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ABG_Tile_Statics::NewProp_tileMesh = { "tileMesh", nullptr, (EPropertyFlags)0x001000000008000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_Tile, tileMesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tileMesh_MetaData), NewProp_tileMesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ABG_Tile_Statics::NewProp_decalComponent = { "decalComponent", nullptr, (EPropertyFlags)0x001000000008000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_Tile, decalComponent), Z_Construct_UClass_UDecalComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_decalComponent_MetaData), NewProp_decalComponent_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ABG_Tile_Statics::NewProp_gridCoordinates = { "gridCoordinates", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_Tile, gridCoordinates), Z_Construct_UScriptStruct_FIntPoint, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_gridCoordinates_MetaData), NewProp_gridCoordinates_MetaData) };
void Z_Construct_UClass_ABG_Tile_Statics::NewProp_isOccupied_SetBit(void* Obj)
{
	((ABG_Tile*)Obj)->isOccupied = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ABG_Tile_Statics::NewProp_isOccupied = { "isOccupied", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ABG_Tile), &Z_Construct_UClass_ABG_Tile_Statics::NewProp_isOccupied_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_isOccupied_MetaData), NewProp_isOccupied_MetaData) };
void Z_Construct_UClass_ABG_Tile_Statics::NewProp_isSpawnableTile_SetBit(void* Obj)
{
	((ABG_Tile*)Obj)->isSpawnableTile = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ABG_Tile_Statics::NewProp_isSpawnableTile = { "isSpawnableTile", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ABG_Tile), &Z_Construct_UClass_ABG_Tile_Statics::NewProp_isSpawnableTile_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_isSpawnableTile_MetaData), NewProp_isSpawnableTile_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ABG_Tile_Statics::NewProp_HexDecalMID = { "HexDecalMID", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_Tile, HexDecalMID), Z_Construct_UClass_UMaterialInstanceDynamic_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HexDecalMID_MetaData), NewProp_HexDecalMID_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_ABG_Tile_Statics::NewProp_owningPlayer_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_ABG_Tile_Statics::NewProp_owningPlayer = { "owningPlayer", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_Tile, owningPlayer), Z_Construct_UEnum_ProductionProjCurr_EActivePlayerSide, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_owningPlayer_MetaData), NewProp_owningPlayer_MetaData) }; // 285499111
const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_ABG_Tile_Statics::NewProp_TileHueParameterName = { "TileHueParameterName", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_Tile, TileHueParameterName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TileHueParameterName_MetaData), NewProp_TileHueParameterName_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABG_Tile_Statics::NewProp_TileHueSaturation = { "TileHueSaturation", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_Tile, TileHueSaturation), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TileHueSaturation_MetaData), NewProp_TileHueSaturation_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABG_Tile_Statics::NewProp_TileHueValue = { "TileHueValue", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_Tile, TileHueValue), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TileHueValue_MetaData), NewProp_TileHueValue_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ABG_Tile_Statics::NewProp_TileMeshMID = { "TileMeshMID", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_Tile, TileMeshMID), Z_Construct_UClass_UMaterialInstanceDynamic_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TileMeshMID_MetaData), NewProp_TileMeshMID_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ABG_Tile_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_Tile_Statics::NewProp_occupyingTroopClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_Tile_Statics::NewProp_currentHighlightType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_Tile_Statics::NewProp_currentHighlightType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_Tile_Statics::NewProp_bCanSpawnTroopOnTile,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_Tile_Statics::NewProp_bBuildingCanBePlacedOnTile,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_Tile_Statics::NewProp_occupyingBuildingClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_Tile_Statics::NewProp_OnTileSelectedDelegate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_Tile_Statics::NewProp_tileMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_Tile_Statics::NewProp_decalComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_Tile_Statics::NewProp_gridCoordinates,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_Tile_Statics::NewProp_isOccupied,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_Tile_Statics::NewProp_isSpawnableTile,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_Tile_Statics::NewProp_HexDecalMID,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_Tile_Statics::NewProp_owningPlayer_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_Tile_Statics::NewProp_owningPlayer,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_Tile_Statics::NewProp_TileHueParameterName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_Tile_Statics::NewProp_TileHueSaturation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_Tile_Statics::NewProp_TileHueValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_Tile_Statics::NewProp_TileMeshMID,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ABG_Tile_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ABG_Tile_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_ProductionProjCurr,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ABG_Tile_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FImplementedInterfaceParams Z_Construct_UClass_ABG_Tile_Statics::InterfaceParams[] = {
	{ Z_Construct_UClass_UInteractionInterface_NoRegister, (int32)VTABLE_OFFSET(ABG_Tile, IInteractionInterface), false },  // 1406007049
};
const UECodeGen_Private::FClassParams Z_Construct_UClass_ABG_Tile_Statics::ClassParams = {
	&ABG_Tile::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_ABG_Tile_Statics::PropPointers,
	InterfaceParams,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_ABG_Tile_Statics::PropPointers),
	UE_ARRAY_COUNT(InterfaceParams),
	0x009001A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ABG_Tile_Statics::Class_MetaDataParams), Z_Construct_UClass_ABG_Tile_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ABG_Tile()
{
	if (!Z_Registration_Info_UClass_ABG_Tile.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ABG_Tile.OuterSingleton, Z_Construct_UClass_ABG_Tile_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ABG_Tile.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ABG_Tile);
ABG_Tile::~ABG_Tile() {}
// ********** End Class ABG_Tile *******************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_tileSpawningLogic_BG_Tile_h__Script_ProductionProjCurr_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ABG_Tile, ABG_Tile::StaticClass, TEXT("ABG_Tile"), &Z_Registration_Info_UClass_ABG_Tile, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ABG_Tile), 1046731506U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_tileSpawningLogic_BG_Tile_h__Script_ProductionProjCurr_2709535097(TEXT("/Script/ProductionProjCurr"),
	Z_CompiledInDeferFile_FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_tileSpawningLogic_BG_Tile_h__Script_ProductionProjCurr_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_tileSpawningLogic_BG_Tile_h__Script_ProductionProjCurr_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
