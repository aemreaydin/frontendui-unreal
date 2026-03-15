#pragma once

#include "CoreMinimal.h"
#include "FrontendEnumTypes.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FrontendUISubsystem.generated.h"

class UFrontendCommonButtonBase;
struct FGameplayTag;
class UFrontendActivatableWidget;
class UFrontendPrimaryLayoutWidget;

enum class EAsyncPushWidgetState : uint8
{
	OnCreateBeforePush,
	AfterPush
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonHoveredUpdateDescription, UFrontendCommonButtonBase*, Button,
                                             FText, DescriptionText);

using FPushCallbackType = const TFunction<void(
	EAsyncPushWidgetState, UFrontendActivatableWidget*)>;

UCLASS()
class FRONTENDUI_API UFrontendUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static UFrontendUISubsystem* Get(const UObject* WorldContextObject);
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	UFUNCTION(BlueprintCallable)
	void RegisterPrimaryLayoutWidget(UFrontendPrimaryLayoutWidget* LayoutWidget);

	void Async_PushWidgetToStack(const FGameplayTag& WidgetTag,
	                             TSoftClassPtr<UFrontendActivatableWidget> LayoutWidgetClass,
	                             const TFunction<void(EAsyncPushWidgetState, UFrontendActivatableWidget*)>&
	                             PushCallback) const;

	void Async_PushConfirmationScreenToModalStack(EConfirmationScreenType ConfirmationType, const FText& Title,
	                                              const FText& Message,
	                                              TFunction<void(EConfirmationScreenButtonType)> OnClickedCallback)
	const;

private:
	UPROPERTY(Transient)
	TObjectPtr<UFrontendPrimaryLayoutWidget> PrimaryLayoutWidget;

public:
	UPROPERTY(BlueprintAssignable)
	FOnButtonHoveredUpdateDescription OnButtonHoveredUpdateDescription;
};
