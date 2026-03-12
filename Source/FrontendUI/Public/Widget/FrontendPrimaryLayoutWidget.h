#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GameplayTagContainer.h"
#include "FrontendPrimaryLayoutWidget.generated.h"

class UCommonActivatableWidgetContainerBase;

UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UFrontendPrimaryLayoutWidget : public UCommonUserWidget
{
	GENERATED_BODY()

	UPROPERTY(Transient)
	TMap<FGameplayTag, TObjectPtr<UCommonActivatableWidgetContainerBase>> WidgetStack;

protected:
	UFUNCTION(BlueprintCallable)
	void PushWidget(UPARAM(meta = (Categories = "Frontend.WidgetStack")) FGameplayTag WidgetTag,
	                UCommonActivatableWidgetContainerBase* Widget);

public:
	UCommonActivatableWidgetContainerBase* GetWidgetByTag(FGameplayTag WidgetTag) const;
};
