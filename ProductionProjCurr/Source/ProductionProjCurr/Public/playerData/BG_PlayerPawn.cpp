#include "BG_PlayerPawn.h" 
#include <tileSpawningLogic/BG_Tile.h>

ABG_PlayerPawn::ABG_PlayerPawn()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));	
	springArm->SetupAttachment(RootComponent);
	springArm->bUsePawnControlRotation = true;
	springArm->bDoCollisionTest = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(springArm);
	Camera->bUsePawnControlRotation = false;

	SpectatorMovementComponent = CreateDefaultSubobject<USpectatorPawnMovement>(TEXT("MovementComponent"));
	SpectatorMovementComponent->UpdatedComponent = RootComponent;

	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void ABG_PlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	if (devMenuWidgetRef)
	{
		devMenuWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), devMenuWidgetRef);
		
		if (devMenuWidgetInstance)
		{
			devMenuWidgetInstance->AddToViewport();
			devMenuWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create dev menu widget!"));
		}
	}
}

void ABG_PlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABG_PlayerPawn::ToggleDevMenu()
{
	if (devMenuWidgetInstance)
	{
		ESlateVisibility currentVisibility = devMenuWidgetInstance->GetVisibility();
		if (currentVisibility == ESlateVisibility::Visible)
		{
			devMenuWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			devMenuWidgetInstance->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void ABG_PlayerPawn::AdjustCameraZoom(float desiredOrthoWidth)
{
	if (Camera)
	{
		Camera->OrthoWidth = FMath::Clamp(desiredOrthoWidth, 500.0f, 10000.0f);
	}
}
