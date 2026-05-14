#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BG_AC_MouseOverlapReciever.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRODUCTIONPROJCURR_API UBG_AC_MouseOverlapReciever : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UBG_AC_MouseOverlapReciever();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
