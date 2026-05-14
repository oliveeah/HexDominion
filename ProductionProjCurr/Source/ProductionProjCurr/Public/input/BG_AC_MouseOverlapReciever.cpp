#include "BG_AC_MouseOverlapReciever.h"

UBG_AC_MouseOverlapReciever::UBG_AC_MouseOverlapReciever()
{
	
	PrimaryComponentTick.bCanEverTick = true;

}

void UBG_AC_MouseOverlapReciever::BeginPlay()
{
	Super::BeginPlay();

}

void UBG_AC_MouseOverlapReciever::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}
