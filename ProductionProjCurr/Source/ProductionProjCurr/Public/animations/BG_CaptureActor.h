#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BG_CaptureActor.generated.h"

UCLASS()
class PRODUCTIONPROJCURR_API ABG_CaptureActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ABG_CaptureActor();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

};
