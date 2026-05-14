#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputAction.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpectatorPawnMovement.h"

#include "DevMode_Widget.h"

#include "playerData/InteractionInterface.h"
#include "BG_PlayerPawn.generated.h"

UCLASS()
class PRODUCTIONPROJCURR_API ABG_PlayerPawn : public APawn
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* springArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	class USpectatorPawnMovement* SpectatorMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="3D UI")
	USkeletalMeshComponent* UI_FactionCharacter;
protected:

protected:
	
	virtual void BeginPlay() override;

public:		
	
	ABG_PlayerPawn();
	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> devMenuWidgetRef;
	UPROPERTY()
	class UUserWidget* devMenuWidgetInstance; 

	void ToggleDevMenu();

	void AdjustCameraZoom(float desiredOrthoWidth);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float ZoomSpeed = 10.0f;
	
};
