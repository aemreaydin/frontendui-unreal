#pragma once

#include "CommonActivatableWidget.h"
#include "CoreMinimal.h"
#include "FrontendActivatableWidget.generated.h"

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UFrontendActivatableWidget
    : public UCommonActivatableWidget {
  GENERATED_BODY()
};
