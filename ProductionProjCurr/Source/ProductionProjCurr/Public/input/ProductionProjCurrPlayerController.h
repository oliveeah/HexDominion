// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "playerData/InteractionInterface.h"
#include "Sound/SoundBase.h"
#include "ProductionProjCurrPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class ABG_PlayerPawn;

/**
 *  Basic PlayerController class for a third person game
 *  Manages input mappings
 */
UCLASS()
class PRODUCTIONPROJCURR_API AProductionProjCurrPlayerController : public APlayerController, public IInteractionInterface
{
	GENERATED_BODY()

public:
	AProductionProjCurrPlayerController();


	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions")
	UInputAction* moveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions")
	UInputAction* lookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions")
	UInputAction* clickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions")
	UInputAction* scrollAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions")
	UInputAction* openDevMenu;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Contexts")
	TArray<UInputMappingContext*> DefaultMappingContexts;

	UPROPERTY(EditAnywhere, Category = "SFX")
	USoundBase* ClickSFX = nullptr;

	// ========== INPUT CALLBACKS (MOVED FROM PAWN) ==========
	void MoveCallback(const FInputActionValue& Value);
	void LookCallback(const FInputActionValue& Value);
	void ClickCallback();
	void ScrollCallback(const FInputActionValue& Value);
	void OpenDevMenuCallback(const FInputActionValue& Value);


private:
	// Cache reference to controlled pawn
	UPROPERTY()
	ABG_PlayerPawn* ControlledPawn;

	// Helper function to get controlled pawn
	ABG_PlayerPawn* GetControlledPawn() const;
};
