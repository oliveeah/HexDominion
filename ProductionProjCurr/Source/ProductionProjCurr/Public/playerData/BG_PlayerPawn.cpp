// Fill out your copyright notice in the Description page of Project Settings.


#include "BG_PlayerPawn.h" //must be at top
#include <tileSpawningLogic/BG_Tile.h>




// Sets default values
ABG_PlayerPawn::ABG_PlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Root component
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//spring arm
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));	
	springArm->SetupAttachment(RootComponent);
	springArm->bUsePawnControlRotation = true;
	springArm->bDoCollisionTest = false;

	// Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(springArm);
	Camera->bUsePawnControlRotation = false;

	// spectator movement
	SpectatorMovementComponent = CreateDefaultSubobject<USpectatorPawnMovement>(TEXT("MovementComponent"));
	SpectatorMovementComponent->UpdatedComponent = RootComponent;

	// Control settings
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	//UI
	//UI_FactionCharacter = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("faction UI character"));
	//UI_FactionCharacter->SetupAttachment(Camera);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}





// Called when the game starts or when spawned
void ABG_PlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	/*developer*/
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

// Called every frame
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

