#pragma once

#include "CommonActivatableWidget.h"
#include "CoreMinimal.h"
#include "FrontendActivatableWidget.generated.h"

class AFrontendPlayerController;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UFrontendActivatableWidget
	: public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintPure)
	AFrontendPlayerController* GetOwningPlayerController();

private:
	UPROPERTY()
	TObjectPtr<AFrontendPlayerController> CachedPlayerController;
};
