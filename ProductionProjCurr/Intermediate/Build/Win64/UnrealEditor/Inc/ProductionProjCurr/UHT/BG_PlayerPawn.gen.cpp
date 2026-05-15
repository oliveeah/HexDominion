// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "playerData/BG_PlayerPawn.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeBG_PlayerPawn() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
ENGINE_API UClass* Z_Construct_UClass_APawn();
ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USkeletalMeshComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USpectatorPawnMovement_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent_NoRegister();
PRODUCTIONPROJCURR_API UClass* Z_Construct_UClass_ABG_PlayerPawn();
PRODUCTIONPROJCURR_API UClass* Z_Construct_UClass_ABG_PlayerPawn_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget_NoRegister();
UPackage* Z_Construct_UPackage__Script_ProductionProjCurr();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ABG_PlayerPawn ***********************************************************
void ABG_PlayerPawn::StaticRegisterNativesABG_PlayerPawn()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_ABG_PlayerPawn;
UClass* ABG_PlayerPawn::GetPrivateStaticClass()
{
	using TClass = ABG_PlayerPawn;
	if (!Z_Registration_Info_UClass_ABG_PlayerPawn.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("BG_PlayerPawn"),
			Z_Registration_Info_UClass_ABG_PlayerPawn.InnerSingleton,
			StaticRegisterNativesABG_PlayerPawn,
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
	return Z_Registration_Info_UClass_ABG_PlayerPawn.InnerSingleton;
}
UClass* Z_Construct_UClass_ABG_PlayerPawn_NoRegister()
{
	return ABG_PlayerPawn::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ABG_PlayerPawn_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "playerData/BG_PlayerPawn.h" },
		{ "ModuleRelativePath", "Public/playerData/BG_PlayerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Camera_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Camera" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/playerData/BG_PlayerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_springArm_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Camera" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/playerData/BG_PlayerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpectatorMovementComponent_MetaData[] = {
		{ "Category", "Movement" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/playerData/BG_PlayerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UI_FactionCharacter_MetaData[] = {
		{ "Category", "3D UI" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/playerData/BG_PlayerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_devMenuWidgetRef_MetaData[] = {
		{ "Category", "UI" },
		{ "ModuleRelativePath", "Public/playerData/BG_PlayerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_devMenuWidgetInstance_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/playerData/BG_PlayerPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ZoomSpeed_MetaData[] = {
		{ "Category", "Camera" },
		{ "ModuleRelativePath", "Public/playerData/BG_PlayerPawn.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Camera;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_springArm;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SpectatorMovementComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_UI_FactionCharacter;
	static const UECodeGen_Private::FClassPropertyParams NewProp_devMenuWidgetRef;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_devMenuWidgetInstance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ZoomSpeed;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ABG_PlayerPawn>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ABG_PlayerPawn_Statics::NewProp_Camera = { "Camera", nullptr, (EPropertyFlags)0x00100000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_PlayerPawn, Camera), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Camera_MetaData), NewProp_Camera_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ABG_PlayerPawn_Statics::NewProp_springArm = { "springArm", nullptr, (EPropertyFlags)0x00100000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_PlayerPawn, springArm), Z_Construct_UClass_USpringArmComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_springArm_MetaData), NewProp_springArm_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ABG_PlayerPawn_Statics::NewProp_SpectatorMovementComponent = { "SpectatorMovementComponent", nullptr, (EPropertyFlags)0x00100000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_PlayerPawn, SpectatorMovementComponent), Z_Construct_UClass_USpectatorPawnMovement_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpectatorMovementComponent_MetaData), NewProp_SpectatorMovementComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ABG_PlayerPawn_Statics::NewProp_UI_FactionCharacter = { "UI_FactionCharacter", nullptr, (EPropertyFlags)0x001000000008000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_PlayerPawn, UI_FactionCharacter), Z_Construct_UClass_USkeletalMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UI_FactionCharacter_MetaData), NewProp_UI_FactionCharacter_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_ABG_PlayerPawn_Statics::NewProp_devMenuWidgetRef = { "devMenuWidgetRef", nullptr, (EPropertyFlags)0x0014000000010001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_PlayerPawn, devMenuWidgetRef), Z_Construct_UClass_UClass, Z_Construct_UClass_UUserWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_devMenuWidgetRef_MetaData), NewProp_devMenuWidgetRef_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ABG_PlayerPawn_Statics::NewProp_devMenuWidgetInstance = { "devMenuWidgetInstance", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_PlayerPawn, devMenuWidgetInstance), Z_Construct_UClass_UUserWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_devMenuWidgetInstance_MetaData), NewProp_devMenuWidgetInstance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABG_PlayerPawn_Statics::NewProp_ZoomSpeed = { "ZoomSpeed", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABG_PlayerPawn, ZoomSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ZoomSpeed_MetaData), NewProp_ZoomSpeed_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ABG_PlayerPawn_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_PlayerPawn_Statics::NewProp_Camera,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_PlayerPawn_Statics::NewProp_springArm,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_PlayerPawn_Statics::NewProp_SpectatorMovementComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_PlayerPawn_Statics::NewProp_UI_FactionCharacter,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_PlayerPawn_Statics::NewProp_devMenuWidgetRef,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_PlayerPawn_Statics::NewProp_devMenuWidgetInstance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABG_PlayerPawn_Statics::NewProp_ZoomSpeed,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ABG_PlayerPawn_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ABG_PlayerPawn_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_APawn,
	(UObject* (*)())Z_Construct_UPackage__Script_ProductionProjCurr,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ABG_PlayerPawn_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ABG_PlayerPawn_Statics::ClassParams = {
	&ABG_PlayerPawn::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ABG_PlayerPawn_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ABG_PlayerPawn_Statics::PropPointers),
	0,
	0x009001A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ABG_PlayerPawn_Statics::Class_MetaDataParams), Z_Construct_UClass_ABG_PlayerPawn_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ABG_PlayerPawn()
{
	if (!Z_Registration_Info_UClass_ABG_PlayerPawn.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ABG_PlayerPawn.OuterSingleton, Z_Construct_UClass_ABG_PlayerPawn_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ABG_PlayerPawn.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ABG_PlayerPawn);
ABG_PlayerPawn::~ABG_PlayerPawn() {}
// ********** End Class ABG_PlayerPawn *************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_playerData_BG_PlayerPawn_h__Script_ProductionProjCurr_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ABG_PlayerPawn, ABG_PlayerPawn::StaticClass, TEXT("ABG_PlayerPawn"), &Z_Registration_Info_UClass_ABG_PlayerPawn, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ABG_PlayerPawn), 4112098612U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_playerData_BG_PlayerPawn_h__Script_ProductionProjCurr_903001100(TEXT("/Script/ProductionProjCurr"),
	Z_CompiledInDeferFile_FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_playerData_BG_PlayerPawn_h__Script_ProductionProjCurr_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_playerData_BG_PlayerPawn_h__Script_ProductionProjCurr_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
