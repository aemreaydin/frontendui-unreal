#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "FrontendActivatableWidget.generated.h"

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UFrontendActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
};
