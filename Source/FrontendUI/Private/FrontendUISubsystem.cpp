#include "FrontendUISubsystem.h"

#include "FrontendBlueprintFunctionLibrary.h"
#include "FrontendGameplayTags.h"
#include "Engine/AssetManager.h"
#include "FrontendUI/Public/Widget/FrontendPrimaryLayoutWidget.h"
#include "Widget/FrontendActivatableWidget.h"
#include "../Public/Widget/FrontendConfirmationWidget.h"
#include "Widgets/CommonActivatableWidgetContainer.h"


UFrontendUISubsystem* UFrontendUISubsystem::Get(const UObject* WorldContextObject)
{
	if (!GEngine)
	{
		return nullptr;
	}

	const auto* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert);
	return UGameInstance::GetSubsystem<UFrontendUISubsystem>(World->GetGameInstance());
}

bool UFrontendUISubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!CastChecked<UGameInstance>(Outer)->IsDedicatedServerInstance())
	{
		TArray<UClass*> FoundClasses;
		GetDerivedClasses(GetClass(), FoundClasses);
		return FoundClasses.IsEmpty();
	}

	return false;
}

void UFrontendUISubsystem::RegisterPrimaryLayoutWidget(UFrontendPrimaryLayoutWidget* LayoutWidget)
{
	check(LayoutWidget);
	PrimaryLayoutWidget = LayoutWidget;
}


void UFrontendUISubsystem::Async_PushWidgetToStack(const FGameplayTag& WidgetTag,
                                                   const TSoftClassPtr<UFrontendActivatableWidget>
                                                   LayoutWidgetClass,
                                                   FPushCallbackType& PushCallback) const
{
	check(!LayoutWidgetClass.IsNull());

	const auto LoadWidget = [this, WidgetTag, LayoutWidgetClass, PushCallback]()
	{
		auto* LoadedWidget = LayoutWidgetClass.Get();

		check(PrimaryLayoutWidget && LoadedWidget);

		auto* FoundWidget = PrimaryLayoutWidget->GetWidgetByTag(WidgetTag);
		auto* CreatedWidget = FoundWidget->AddWidget<UFrontendActivatableWidget>(
			LoadedWidget,
			[&](UFrontendActivatableWidget& ActivatableWidget)
			{
				PushCallback(EAsyncPushWidgetState::OnCreateBeforePush, &ActivatableWidget);
			});

		PushCallback(EAsyncPushWidgetState::AfterPush, CreatedWidget);
	};

	UAssetManager::Get().GetStreamableManager()
	                    .RequestAsyncLoad(LayoutWidgetClass.ToSoftObjectPath(),
	                                      FStreamableDelegate::CreateLambda(LoadWidget));
}

void UFrontendUISubsystem::Async_PushConfirmationScreenToModalStack(const EConfirmationScreenType ConfirmationType,
                                                                    const FText& Title, const FText& Message,
                                                                    TFunction<void(EConfirmationScreenButtonType)>
                                                                    OnClickedCallback) const
{
	UConfirmationScreenInfoObject* ConfirmationScreenInfo{nullptr};

	switch (ConfirmationType)
	{
	case EConfirmationScreenType::Ok:
		ConfirmationScreenInfo = UConfirmationScreenInfoObject::CreateOkScreenInfo(Title, Message);
		break;
	case EConfirmationScreenType::YesNo:
		ConfirmationScreenInfo = UConfirmationScreenInfoObject::CreateYesNoScreenInfo(Title, Message);
		break;
	case EConfirmationScreenType::OkCancel:
		ConfirmationScreenInfo = UConfirmationScreenInfoObject::CreateOkCancelScreenInfo(Title, Message);
		break;
	case EConfirmationScreenType::Unknown:
		break;
	default: ;
	}
	check(ConfirmationScreenInfo);
	
	ConfirmationScreenInfo->ConfirmationTitle = Title;
	ConfirmationScreenInfo->ConfirmationMessage = Message;

	const auto ConfirmationWidgetClass = UFrontendBlueprintFunctionLibrary::GetActivatableWidgetByTag(
		FrontendGameplayTags::Frontend_Widget_ConfirmationScreen);

	Async_PushWidgetToStack(FrontendGameplayTags::Frontend_WidgetStack_Modal, ConfirmationWidgetClass,
	                        [ConfirmationScreenInfo, OnClickedCallback](const EAsyncPushWidgetState State,
	                                                                    UFrontendActivatableWidget* Widget)
	                        {
		                        if (State == EAsyncPushWidgetState::OnCreateBeforePush)
		                        {
			                        auto* ConfirmationWidget = CastChecked<UFrontendConfirmationWidget>(Widget);
			                        ConfirmationWidget->InitConfirmScreen(ConfirmationScreenInfo, OnClickedCallback);
		                        }
	                        });
}
