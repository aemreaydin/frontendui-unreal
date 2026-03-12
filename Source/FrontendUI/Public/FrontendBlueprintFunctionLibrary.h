#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "FrontendBlueprintFunctionLibrary.generated.h"

class UFrontendActivatableWidget;

UCLASS()
class FRONTENDUI_API UFrontendBlueprintFunctionLibrary
	: public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Frontend Blueprint Library")
	static TSoftClassPtr<UFrontendActivatableWidget>
	GetActivatableWidgetByTag(UPARAM(meta = (Categories = "Frontend.Widget"))
		FGameplayTag GameplayTag);
};
