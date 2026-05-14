#include "ProductionProjCurrPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Kismet/GameplayStatics.h"
#include "playerData/BG_PlayerPawn.h"

AProductionProjCurrPlayerController::AProductionProjCurrPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AProductionProjCurrPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

	FInputModeGameAndUI InputMode;
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);

}

void AProductionProjCurrPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
		{
			if (CurrentContext)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}
		}
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (moveAction)
		{
			EnhancedInputComponent->BindAction(moveAction, ETriggerEvent::Triggered, this, &AProductionProjCurrPlayerController::MoveCallback);
		}

		if (lookAction)
		{
			EnhancedInputComponent->BindAction(lookAction, ETriggerEvent::Triggered, this, &AProductionProjCurrPlayerController::LookCallback);
		}

		if (clickAction)
		{
			EnhancedInputComponent->BindAction(clickAction, ETriggerEvent::Started, this, &AProductionProjCurrPlayerController::ClickCallback);
		}

		if (scrollAction)
		{
			EnhancedInputComponent->BindAction(scrollAction, ETriggerEvent::Triggered, this, &AProductionProjCurrPlayerController::ScrollCallback);
		}

		if (openDevMenu)
		{
			EnhancedInputComponent->BindAction(openDevMenu, ETriggerEvent::Started, this, &AProductionProjCurrPlayerController::OpenDevMenuCallback);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController: Failed to find Enhanced Input Component!"));
	}
}

void AProductionProjCurrPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	ControlledPawn = Cast<ABG_PlayerPawn>(InPawn);
	
	if (!ControlledPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessed a non-BG_PlayerPawn!"));
	}		
}

ABG_PlayerPawn* AProductionProjCurrPlayerController::GetControlledPawn() const
{
	if (!ControlledPawn)
	{
		return Cast<ABG_PlayerPawn>(GetPawn());
	}
	return ControlledPawn;
}

void AProductionProjCurrPlayerController::MoveCallback(const FInputActionValue& Value)
{
	ABG_PlayerPawn* _ControlledPawn = GetControlledPawn();
	if (!_ControlledPawn)
	{
		return;
	}

	const FVector2D MovementVector = Value.Get<FVector2D>();
	
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
	ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
}

void AProductionProjCurrPlayerController::LookCallback(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddYawInput(LookAxisVector.X);
}

void AProductionProjCurrPlayerController::ClickCallback()
{
	
	if (ClickSFX)
	{
		UGameplayStatics::PlaySound2D(this, ClickSFX);
	}

	FHitResult HitResult;
	bool bHit = GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

	if (bHit && HitResult.GetActor())
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor && HitActor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
		{
			IInteractionInterface::Execute_ReactToPlayerInteraction(HitActor);
		}
	}
}

void AProductionProjCurrPlayerController::ScrollCallback(const FInputActionValue& Value)
{
	ABG_PlayerPawn* _ControlledPawn = GetControlledPawn();
	if (!_ControlledPawn)
	{
		return;
	}

	const float ZoomDir = Value.Get<float>();
	const float desiredOrthoWidth = _ControlledPawn->Camera->OrthoWidth + ZoomDir * _ControlledPawn->ZoomSpeed;
	_ControlledPawn->AdjustCameraZoom(desiredOrthoWidth);
}

void AProductionProjCurrPlayerController::OpenDevMenuCallback(const FInputActionValue& Value)
{
	ABG_PlayerPawn* _ControlledPawn = GetControlledPawn();
	if (!_ControlledPawn)
	{
		return;
	}

	_ControlledPawn->ToggleDevMenu();
}
