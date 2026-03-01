#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "FrontendAsyncActionPushSoftWidget.generated.h"

class UFrontendActivatableWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPushSoftWidgetDelegate, UFrontendActivatableWidget*, PushedWidget);

UCLASS()
class FRONTENDUI_API UFrontendAsyncActionPushSoftWidget : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable,
		meta = (WorldContext = "WorldContextObject", HidePin = "WorldContextObject", BlueprintInternalUseOnly = "true",
			DisplayName = "Push Soft Widget To Stack"))
	static UFrontendAsyncActionPushSoftWidget* PushSoftWidget(const UObject* WorldContextObject,
	                                                          APlayerController* PlayerController,
	                                                          TSoftClassPtr<UFrontendActivatableWidget>
	                                                          ActivatableWidgetClass,
	                                                          UPARAM(meta = (Categories = "Frontend.WidgetStack"))
	                                                          FGameplayTag WidgetStackTag,
	                                                          bool bFocusOnPushedWidget = true);
	virtual void Activate() override;

	UPROPERTY(BlueprintAssignable)
	FOnPushSoftWidgetDelegate OnCreatedBeforePush;

	UPROPERTY(BlueprintAssignable)
	FOnPushSoftWidgetDelegate OnAfterPush;

private:
	TWeakObjectPtr<UWorld> CachedWorld;
	TWeakObjectPtr<APlayerController> CachedPlayerController;
	TSoftClassPtr<UFrontendActivatableWidget> CachedActivatableWidgetClass;
	FGameplayTag CachedWidgetStackTag;
	bool bCachedFocusOnPushedWidget;
};
