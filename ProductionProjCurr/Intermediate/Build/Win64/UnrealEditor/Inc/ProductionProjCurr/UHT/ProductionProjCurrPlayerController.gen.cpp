// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "input/ProductionProjCurrPlayerController.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeProductionProjCurrPlayerController() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_APlayerController();
ENGINE_API UClass* Z_Construct_UClass_USoundBase_NoRegister();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction_NoRegister();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputMappingContext_NoRegister();
PRODUCTIONPROJCURR_API UClass* Z_Construct_UClass_ABG_PlayerPawn_NoRegister();
PRODUCTIONPROJCURR_API UClass* Z_Construct_UClass_AProductionProjCurrPlayerController();
PRODUCTIONPROJCURR_API UClass* Z_Construct_UClass_AProductionProjCurrPlayerController_NoRegister();
PRODUCTIONPROJCURR_API UClass* Z_Construct_UClass_UInteractionInterface_NoRegister();
UPackage* Z_Construct_UPackage__Script_ProductionProjCurr();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AProductionProjCurrPlayerController **************************************
void AProductionProjCurrPlayerController::StaticRegisterNativesAProductionProjCurrPlayerController()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_AProductionProjCurrPlayerController;
UClass* AProductionProjCurrPlayerController::GetPrivateStaticClass()
{
	using TClass = AProductionProjCurrPlayerController;
	if (!Z_Registration_Info_UClass_AProductionProjCurrPlayerController.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("ProductionProjCurrPlayerController"),
			Z_Registration_Info_UClass_AProductionProjCurrPlayerController.InnerSingleton,
			StaticRegisterNativesAProductionProjCurrPlayerController,
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
	return Z_Registration_Info_UClass_AProductionProjCurrPlayerController.InnerSingleton;
}
UClass* Z_Construct_UClass_AProductionProjCurrPlayerController_NoRegister()
{
	return AProductionProjCurrPlayerController::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AProductionProjCurrPlayerController_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Basic PlayerController class for a third person game\n *  Manages input mappings\n */" },
#endif
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "input/ProductionProjCurrPlayerController.h" },
		{ "ModuleRelativePath", "Public/input/ProductionProjCurrPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Basic PlayerController class for a third person game\nManages input mappings" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_moveAction_MetaData[] = {
		{ "Category", "Input|Actions" },
		{ "ModuleRelativePath", "Public/input/ProductionProjCurrPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_lookAction_MetaData[] = {
		{ "Category", "Input|Actions" },
		{ "ModuleRelativePath", "Public/input/ProductionProjCurrPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_clickAction_MetaData[] = {
		{ "Category", "Input|Actions" },
		{ "ModuleRelativePath", "Public/input/ProductionProjCurrPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_scrollAction_MetaData[] = {
		{ "Category", "Input|Actions" },
		{ "ModuleRelativePath", "Public/input/ProductionProjCurrPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_openDevMenu_MetaData[] = {
		{ "Category", "Input|Actions" },
		{ "ModuleRelativePath", "Public/input/ProductionProjCurrPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultMappingContexts_MetaData[] = {
		{ "Category", "Input|Contexts" },
		{ "ModuleRelativePath", "Public/input/ProductionProjCurrPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ClickSFX_MetaData[] = {
		{ "Category", "SFX" },
		{ "ModuleRelativePath", "Public/input/ProductionProjCurrPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ControlledPawn_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Cache reference to controlled pawn\n" },
#endif
		{ "ModuleRelativePath", "Public/input/ProductionProjCurrPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Cache reference to controlled pawn" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_moveAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_lookAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_clickAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_scrollAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_openDevMenu;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DefaultMappingContexts_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_DefaultMappingContexts;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ClickSFX;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ControlledPawn;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static const UECodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AProductionProjCurrPlayerController>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AProductionProjCurrPlayerController_Statics::NewProp_moveAction = { "moveAction", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AProductionProjCurrPlayerController, moveAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_moveAction_MetaData), NewProp_moveAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AProductionProjCurrPlayerController_Statics::NewProp_lookAction = { "lookAction", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AProductionProjCurrPlayerController, lookAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_lookAction_MetaData), NewProp_lookAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AProductionProjCurrPlayerController_Statics::NewProp_clickAction = { "clickAction", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AProductionProjCurrPlayerController, clickAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_clickAction_MetaData), NewProp_clickAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AProductionProjCurrPlayerController_Statics::NewProp_scrollAction = { "scrollAction", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AProductionProjCurrPlayerController, scrollAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_scrollAction_MetaData), NewProp_scrollAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AProductionProjCurrPlayerController_Statics::NewProp_openDevMenu = { "openDevMenu", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AProductionProjCurrPlayerController, openDevMenu), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_openDevMenu_MetaData), NewProp_openDevMenu_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AProductionProjCurrPlayerController_Statics::NewProp_DefaultMappingContexts_Inner = { "DefaultMappingContexts", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UInputMappingContext_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AProductionProjCurrPlayerController_Statics::NewProp_DefaultMappingContexts = { "DefaultMappingContexts", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AProductionProjCurrPlayerController, DefaultMappingContexts), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultMappingContexts_MetaData), NewProp_DefaultMappingContexts_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AProductionProjCurrPlayerController_Statics::NewProp_ClickSFX = { "ClickSFX", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AProductionProjCurrPlayerController, ClickSFX), Z_Construct_UClass_USoundBase_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ClickSFX_MetaData), NewProp_ClickSFX_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AProductionProjCurrPlayerController_Statics::NewProp_ControlledPawn = { "ControlledPawn", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AProductionProjCurrPlayerController, ControlledPawn), Z_Construct_UClass_ABG_PlayerPawn_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ControlledPawn_MetaData), NewProp_ControlledPawn_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AProductionProjCurrPlayerController_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProductionProjCurrPlayerController_Statics::NewProp_moveAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProductionProjCurrPlayerController_Statics::NewProp_lookAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProductionProjCurrPlayerController_Statics::NewProp_clickAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProductionProjCurrPlayerController_Statics::NewProp_scrollAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProductionProjCurrPlayerController_Statics::NewProp_openDevMenu,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProductionProjCurrPlayerController_Statics::NewProp_DefaultMappingContexts_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProductionProjCurrPlayerController_Statics::NewProp_DefaultMappingContexts,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProductionProjCurrPlayerController_Statics::NewProp_ClickSFX,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProductionProjCurrPlayerController_Statics::NewProp_ControlledPawn,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AProductionProjCurrPlayerController_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AProductionProjCurrPlayerController_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_APlayerController,
	(UObject* (*)())Z_Construct_UPackage__Script_ProductionProjCurr,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AProductionProjCurrPlayerController_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FImplementedInterfaceParams Z_Construct_UClass_AProductionProjCurrPlayerController_Statics::InterfaceParams[] = {
	{ Z_Construct_UClass_UInteractionInterface_NoRegister, (int32)VTABLE_OFFSET(AProductionProjCurrPlayerController, IInteractionInterface), false },  // 1406007049
};
const UECodeGen_Private::FClassParams Z_Construct_UClass_AProductionProjCurrPlayerController_Statics::ClassParams = {
	&AProductionProjCurrPlayerController::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_AProductionProjCurrPlayerController_Statics::PropPointers,
	InterfaceParams,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_AProductionProjCurrPlayerController_Statics::PropPointers),
	UE_ARRAY_COUNT(InterfaceParams),
	0x009003A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AProductionProjCurrPlayerController_Statics::Class_MetaDataParams), Z_Construct_UClass_AProductionProjCurrPlayerController_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AProductionProjCurrPlayerController()
{
	if (!Z_Registration_Info_UClass_AProductionProjCurrPlayerController.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AProductionProjCurrPlayerController.OuterSingleton, Z_Construct_UClass_AProductionProjCurrPlayerController_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AProductionProjCurrPlayerController.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AProductionProjCurrPlayerController);
AProductionProjCurrPlayerController::~AProductionProjCurrPlayerController() {}
// ********** End Class AProductionProjCurrPlayerController ****************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_input_ProductionProjCurrPlayerController_h__Script_ProductionProjCurr_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AProductionProjCurrPlayerController, AProductionProjCurrPlayerController::StaticClass, TEXT("AProductionProjCurrPlayerController"), &Z_Registration_Info_UClass_AProductionProjCurrPlayerController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AProductionProjCurrPlayerController), 313379192U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_input_ProductionProjCurrPlayerController_h__Script_ProductionProjCurr_880521027(TEXT("/Script/ProductionProjCurr"),
	Z_CompiledInDeferFile_FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_input_ProductionProjCurrPlayerController_h__Script_ProductionProjCurr_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_input_ProductionProjCurrPlayerController_h__Script_ProductionProjCurr_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
