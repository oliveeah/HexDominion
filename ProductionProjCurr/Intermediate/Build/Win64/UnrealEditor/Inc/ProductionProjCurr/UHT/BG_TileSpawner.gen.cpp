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
ENGINE_API UClass* Z_Construct_UClass_AActor();
PRODUCTIONPROJCURR_API UClass* Z_Construct_UClass_ABG_TileSpawner();
PRODUCTIONPROJCURR_API UClass* Z_Construct_UClass_ABG_TileSpawner_NoRegister();
PRODUCTIONPROJCURR_API UClass* Z_Construct_UClass_ATileManager_NoRegister();
PRODUCTIONPROJCURR_API UClass* Z_Construct_UClass_UTileSpawner_Data_NoRegister();
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
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TileSpawnerData_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Tile Spawner" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_TileSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TileManager_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "TileManager" },
		{ "ModuleRelativePath", "Public/tileSpawningLogic/BG_TileSpawner.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnGridBuilt;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TileSpawnerData;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TileManager;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ABG_TileSpawner>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_OnGridBuilt = { "OnGridBuilt", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_TileSpawner, OnGridBuilt), Z_Construct_UDelegateFunction_ProductionProjCurr_OnGridBuilt__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnGridBuilt_MetaData), NewProp_OnGridBuilt_MetaData) }; // 4267761514
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_TileSpawnerData = { "TileSpawnerData", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_TileSpawner, TileSpawnerData), Z_Construct_UClass_UTileSpawner_Data_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TileSpawnerData_MetaData), NewProp_TileSpawnerData_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_TileManager = { "TileManager", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_TileSpawner, TileManager), Z_Construct_UClass_ATileManager_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TileManager_MetaData), NewProp_TileManager_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ABG_TileSpawner_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_OnGridBuilt,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_TileSpawnerData,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_TileSpawner_Statics::NewProp_TileManager,
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
		{ Z_Construct_UClass_ABG_TileSpawner, ABG_TileSpawner::StaticClass, TEXT("ABG_TileSpawner"), &Z_Registration_Info_UClass_ABG_TileSpawner, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ABG_TileSpawner), 1086044161U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_tileSpawningLogic_BG_TileSpawner_h__Script_ProductionProjCurr_3966944640(TEXT("/Script/ProductionProjCurr"),
	Z_CompiledInDeferFile_FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_tileSpawningLogic_BG_TileSpawner_h__Script_ProductionProjCurr_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_tileSpawningLogic_BG_TileSpawner_h__Script_ProductionProjCurr_Statics::ClassInfo),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_tileSpawningLogic_BG_TileSpawner_h__Script_ProductionProjCurr_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_tileSpawningLogic_BG_TileSpawner_h__Script_ProductionProjCurr_Statics::EnumInfo));
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
