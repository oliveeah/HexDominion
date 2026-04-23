// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "tileSpawningLogic/BG_Tile.h"

#ifdef PRODUCTIONPROJCURR_BG_Tile_generated_h
#error "BG_Tile.generated.h already included, missing '#pragma once' in BG_Tile.h"
#endif
#define PRODUCTIONPROJCURR_BG_Tile_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

class ABG_Tile;
enum class EActivePlayerSide : uint8;

// ********** Begin Delegate FOnTileSelected *******************************************************
#define FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_tileSpawningLogic_BG_Tile_h_26_DELEGATE \
PRODUCTIONPROJCURR_API void FOnTileSelected_DelegateWrapper(const FMulticastScriptDelegate& OnTileSelected, ABG_Tile* Tile, bool isOccupied);


// ********** End Delegate FOnTileSelected *********************************************************

// ********** Begin Class ABG_Tile *****************************************************************
#define FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_tileSpawningLogic_BG_Tile_h_32_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execSetOwningPlayer);


PRODUCTIONPROJCURR_API UClass* Z_Construct_UClass_ABG_Tile_NoRegister();

#define FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_tileSpawningLogic_BG_Tile_h_32_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesABG_Tile(); \
	friend struct Z_Construct_UClass_ABG_Tile_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend PRODUCTIONPROJCURR_API UClass* Z_Construct_UClass_ABG_Tile_NoRegister(); \
public: \
	DECLARE_CLASS2(ABG_Tile, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/ProductionProjCurr"), Z_Construct_UClass_ABG_Tile_NoRegister) \
	DECLARE_SERIALIZER(ABG_Tile) \
	virtual UObject* _getUObject() const override { return const_cast<ABG_Tile*>(this); }


#define FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_tileSpawningLogic_BG_Tile_h_32_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ABG_Tile(ABG_Tile&&) = delete; \
	ABG_Tile(const ABG_Tile&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ABG_Tile); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ABG_Tile); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ABG_Tile) \
	NO_API virtual ~ABG_Tile();


#define FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_tileSpawningLogic_BG_Tile_h_29_PROLOG
#define FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_tileSpawningLogic_BG_Tile_h_32_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_tileSpawningLogic_BG_Tile_h_32_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_tileSpawningLogic_BG_Tile_h_32_INCLASS_NO_PURE_DECLS \
	FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_tileSpawningLogic_BG_Tile_h_32_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ABG_Tile;

// ********** End Class ABG_Tile *******************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_linda_Documents_GitHub_Production_Project_2_ProductionProjCurr_Source_ProductionProjCurr_Public_tileSpawningLogic_BG_Tile_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
