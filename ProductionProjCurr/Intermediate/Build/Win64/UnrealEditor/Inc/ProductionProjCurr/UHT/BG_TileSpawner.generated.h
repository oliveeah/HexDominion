// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "tileSpawningLogic/BG_TileSpawner.h"

#ifdef PRODUCTIONPROJCURR_BG_TileSpawner_generated_h
#error "BG_TileSpawner.generated.h already included, missing '#pragma once' in BG_TileSpawner.h"
#endif
#define PRODUCTIONPROJCURR_BG_TileSpawner_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ABG_TileSpawner **********************************************************
PRODUCTIONPROJCURR_API UClass* Z_Construct_UClass_ABG_TileSpawner_NoRegister();

#define FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_tileSpawningLogic_BG_TileSpawner_h_32_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesABG_TileSpawner(); \
	friend struct Z_Construct_UClass_ABG_TileSpawner_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend PRODUCTIONPROJCURR_API UClass* Z_Construct_UClass_ABG_TileSpawner_NoRegister(); \
public: \
	DECLARE_CLASS2(ABG_TileSpawner, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/ProductionProjCurr"), Z_Construct_UClass_ABG_TileSpawner_NoRegister) \
	DECLARE_SERIALIZER(ABG_TileSpawner)


#define FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_tileSpawningLogic_BG_TileSpawner_h_32_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ABG_TileSpawner(ABG_TileSpawner&&) = delete; \
	ABG_TileSpawner(const ABG_TileSpawner&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ABG_TileSpawner); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ABG_TileSpawner); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ABG_TileSpawner) \
	NO_API virtual ~ABG_TileSpawner();


#define FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_tileSpawningLogic_BG_TileSpawner_h_28_PROLOG
#define FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_tileSpawningLogic_BG_TileSpawner_h_32_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_tileSpawningLogic_BG_TileSpawner_h_32_INCLASS_NO_PURE_DECLS \
	FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_tileSpawningLogic_BG_TileSpawner_h_32_ENHANCED_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ABG_TileSpawner;

// ********** End Class ABG_TileSpawner ************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_tileSpawningLogic_BG_TileSpawner_h

// ********** Begin Enum EBiomeType ****************************************************************
#define FOREACH_ENUM_EBIOMETYPE(op) \
	op(EBiomeType::Water) \
	op(EBiomeType::Sandy) \
	op(EBiomeType::Grassland) \
	op(EBiomeType::Forest) \
	op(EBiomeType::Stone) \
	op(EBiomeType::Hill) \
	op(EBiomeType::Mountain) 

enum class EBiomeType : uint8;
template<> struct TIsUEnumClass<EBiomeType> { enum { Value = true }; };
template<> PRODUCTIONPROJCURR_API UEnum* StaticEnum<EBiomeType>();
// ********** End Enum EBiomeType ******************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
