// 


#include "Async/Action/FrontendAsyncActionPushConfirmationScreen.h"

#include "FrontendUISubsystem.h"

UFrontendAsyncActionPushConfirmationScreen* UFrontendAsyncActionPushConfirmationScreen::PushConfirmationWidget(
	const UObject* WorldContextObject, const FText Title, const FText Message,
	const EConfirmationScreenType ConfirmationScreenType)
{
	if (!GEngine)
	{
		return nullptr;
	}

	if (auto* World = GEngine->
		GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		auto* Node = NewObject<UFrontendAsyncActionPushConfirmationScreen>();

		Node->CachedWorld = World;
		Node->CachedTitle = Title;
		Node->CachedMessage = Message;
		Node->CachedConfirmationScreenType = ConfirmationScreenType;

		Node->RegisterWithGameInstance(World);
		return Node;
	}

	return nullptr;
}

void UFrontendAsyncActionPushConfirmationScreen::Activate()
{
	Super::Activate();

	const auto* FrontendSubsystem = UFrontendUISubsystem::Get(CachedWorld.Get());
	FrontendSubsystem->Async_PushConfirmationScreenToModalStack(CachedConfirmationScreenType, CachedTitle,
	                                                            CachedMessage,
	                                                            [this](
	                                                            const EConfirmationScreenButtonType ClickedButtonType)
	                                                            {
		                                                            OnButtonClicked.Broadcast(ClickedButtonType);
		                                                            SetReadyToDestroy();
	                                                            });
}
