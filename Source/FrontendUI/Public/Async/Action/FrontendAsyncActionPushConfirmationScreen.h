#pragma once

#include "CoreMinimal.h"
#include "FrontendEnumTypes.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "FrontendAsyncActionPushConfirmationScreen.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonClicked, EConfirmationScreenButtonType, ButtonType);

UCLASS()
class FRONTENDUI_API UFrontendAsyncActionPushConfirmationScreen : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable,
		meta = (WorldContext = "WorldContextObject", HidePin = "WorldContextObject", BlueprintInternalUseOnly = "true",
			DisplayName = "Push Confirmation Screen to Modal Stack"))
	static UFrontendAsyncActionPushConfirmationScreen* PushConfirmationWidget(const UObject* WorldContextObject,
	                                                                          const FText Title, const FText Message,
	                                                                          EConfirmationScreenType
	                                                                          ConfirmationScreenType);
	virtual void Activate() override;

	UPROPERTY(BlueprintAssignable)
	FOnButtonClicked OnButtonClicked;

private:
	TWeakObjectPtr<UWorld> CachedWorld;
	FText CachedTitle;
	FText CachedMessage;
	EConfirmationScreenType CachedConfirmationScreenType;
};
