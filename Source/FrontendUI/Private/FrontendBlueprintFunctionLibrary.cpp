#include "FrontendBlueprintFunctionLibrary.h"
#include "DeveloperSettings/FrontendDeveloperSettings.h"
#include "Widget/FrontendActivatableWidget.h"

TSoftClassPtr<UFrontendActivatableWidget>
UFrontendBlueprintFunctionLibrary::GetActivatableWidgetByTag(
	const FGameplayTag GameplayTag)
{
	const auto* FrontendSettings = GetDefault<UFrontendDeveloperSettings>();

	checkf(FrontendSettings->WidgetReferenceMap.Contains(GameplayTag),
	       TEXT("Failed to find gameplay tag."));
	return FrontendSettings->WidgetReferenceMap.FindRef(GameplayTag);
}
