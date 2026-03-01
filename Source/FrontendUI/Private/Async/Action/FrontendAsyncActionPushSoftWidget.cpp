#include "Async/Action/FrontendAsyncActionPushSoftWidget.h"

#include "FrontendUISubsystem.h"
#include "Widget/FrontendActivatableWidget.h"

UFrontendAsyncActionPushSoftWidget* UFrontendAsyncActionPushSoftWidget::PushSoftWidget(
	const UObject* WorldContextObject, APlayerController* PlayerController,
	const TSoftClassPtr<UFrontendActivatableWidget> ActivatableWidgetClass, const FGameplayTag WidgetStackTag,
	const bool bFocusOnPushedWidget)
{
	check(!ActivatableWidgetClass.IsNull());
	if (!GEngine)
	{
		return nullptr;
	}

	if (auto* World = GEngine->
		GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		auto* Node = NewObject<UFrontendAsyncActionPushSoftWidget>();

		Node->CachedWorld = World;
		Node->CachedPlayerController = PlayerController;
		Node->CachedActivatableWidgetClass = ActivatableWidgetClass;
		Node->CachedWidgetStackTag = WidgetStackTag;
		Node->bCachedFocusOnPushedWidget = bFocusOnPushedWidget;

		Node->RegisterWithGameInstance(World);
		return Node;
	}

	return nullptr;
}

void UFrontendAsyncActionPushSoftWidget::Activate()
{
	Super::Activate();

	const auto PushCallback = [&](const EAsyncPushWidgetState State,
	                              UFrontendActivatableWidget* PushedWidget)
	{
		switch (State)
		{
		case EAsyncPushWidgetState::OnCreateBeforePush:
			PushedWidget->SetOwningPlayer(CachedPlayerController.Get());
			OnCreatedBeforePush.Broadcast(PushedWidget);
			break;
		case EAsyncPushWidgetState::AfterPush:
			OnAfterPush.Broadcast(PushedWidget);
			if (bCachedFocusOnPushedWidget)
			{
				if (auto* Widget = PushedWidget->GetDesiredFocusWidget())
				{
					Widget->SetFocus();
				}
			}

			SetReadyToDestroy();
			break;
		default: ;
		}
	};

	const auto* FrontendSubsystem = UFrontendUISubsystem::Get(CachedWorld.Get());
	FrontendSubsystem->Async_PushWidgetToStack(CachedWidgetStackTag,
	                                           CachedActivatableWidgetClass,
	                                           PushCallback);
}
