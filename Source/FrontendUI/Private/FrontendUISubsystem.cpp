#include "FrontendUISubsystem.h"
#include "Engine/AssetManager.h"
#include "FrontendUI/Widget/FrontendPrimaryLayoutWidget.h"
#include "Widget/FrontendActivatableWidget.h"
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
                                                   const TSoftClassPtr<UFrontendActivatableWidget> LayoutWidgetClass,
                                                   FPushCallbackType& PushCallback) const
{
	check(!LayoutWidgetClass.IsNull());

	const auto LoadWidget = [&, LayoutWidgetClass, PushCallback]()
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
