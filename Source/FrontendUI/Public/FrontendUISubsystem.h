#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FrontendUISubsystem.generated.h"

struct FGameplayTag;
class UFrontendActivatableWidget;
class UFrontendPrimaryLayoutWidget;

enum class EAsyncPushWidgetState : uint8
{
	OnCreateBeforePush,
	AfterPush
};

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

private:
	UPROPERTY(Transient)
	TObjectPtr<UFrontendPrimaryLayoutWidget> PrimaryLayoutWidget;
};
