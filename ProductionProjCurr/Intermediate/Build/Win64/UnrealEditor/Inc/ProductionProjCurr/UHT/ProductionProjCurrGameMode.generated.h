// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "gameMode/ProductionProjCurrGameMode.h"

#ifdef PRODUCTIONPROJCURR_ProductionProjCurrGameMode_generated_h
#error "ProductionProjCurrGameMode.generated.h already included, missing '#pragma once' in ProductionProjCurrGameMode.h"
#endif
#define PRODUCTIONPROJCURR_ProductionProjCurrGameMode_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

class ATileManager;

// ********** Begin Delegate FOnToggleTileDebugCoordinates *****************************************
#define FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_gameMode_ProductionProjCurrGameMode_h_13_DELEGATE \
PRODUCTIONPROJCURR_API void FOnToggleTileDebugCoordinates_DelegateWrapper(const FMulticastScriptDelegate& OnToggleTileDebugCoordinates);


// ********** End Delegate FOnToggleTileDebugCoordinates *******************************************

// ********** Begin Class AProductionProjCurrGameMode **********************************************
#define FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_gameMode_ProductionProjCurrGameMode_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetTileManager); \
	DECLARE_FUNCTION(execToggleTileDebugCoordinates);


PRODUCTIONPROJCURR_API UClass* Z_Construct_UClass_AProductionProjCurrGameMode_NoRegister();

#define FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_gameMode_ProductionProjCurrGameMode_h_20_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAProductionProjCurrGameMode(); \
	friend struct Z_Construct_UClass_AProductionProjCurrGameMode_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend PRODUCTIONPROJCURR_API UClass* Z_Construct_UClass_AProductionProjCurrGameMode_NoRegister(); \
public: \
	DECLARE_CLASS2(AProductionProjCurrGameMode, AGameModeBase, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/ProductionProjCurr"), Z_Construct_UClass_AProductionProjCurrGameMode_NoRegister) \
	DECLARE_SERIALIZER(AProductionProjCurrGameMode)


#define FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_gameMode_ProductionProjCurrGameMode_h_20_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AProductionProjCurrGameMode(AProductionProjCurrGameMode&&) = delete; \
	AProductionProjCurrGameMode(const AProductionProjCurrGameMode&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AProductionProjCurrGameMode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AProductionProjCurrGameMode); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(AProductionProjCurrGameMode) \
	NO_API virtual ~AProductionProjCurrGameMode();


#define FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_gameMode_ProductionProjCurrGameMode_h_17_PROLOG
#define FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_gameMode_ProductionProjCurrGameMode_h_20_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_gameMode_ProductionProjCurrGameMode_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_gameMode_ProductionProjCurrGameMode_h_20_INCLASS_NO_PURE_DECLS \
	FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_gameMode_ProductionProjCurrGameMode_h_20_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AProductionProjCurrGameMode;

// ********** End Class AProductionProjCurrGameMode ************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_gameMode_ProductionProjCurrGameMode_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
