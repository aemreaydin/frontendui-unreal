#include "../../Public/Widget/FrontendConfirmationWidget.h"

#include "CommonTextBlock.h"
#include "Components/DynamicEntryBox.h"
#include "Widget/Component/FrontendCommonButtonBase.h"
#include "ICommonInputModule.h"

UConfirmationScreenInfoObject* UConfirmationScreenInfoObject::CreateOkScreenInfo(
	const FText& InConfirmationTitle, const FText& InConfirmationMessage)
{
	FConfirmationButtonInfo ConfirmationButtonInfo;
	ConfirmationButtonInfo.ButtonType = EConfirmationScreenButtonType::Confirm;
	ConfirmationButtonInfo.ButtonText = FText::FromString(TEXT("Confirm"));

	auto* ConfirmationScreenObject = NewObject<UConfirmationScreenInfoObject>();
	ConfirmationScreenObject->ConfirmationMessage = InConfirmationMessage;
	ConfirmationScreenObject->ConfirmationTitle = InConfirmationTitle;
	ConfirmationScreenObject->ConfirmationButtons.Add(ConfirmationButtonInfo);

	return ConfirmationScreenObject;
}

UConfirmationScreenInfoObject* UConfirmationScreenInfoObject::CreateYesNoScreenInfo(const FText& InConfirmationTitle,
	const FText& InConfirmationMessage)
{
	FConfirmationButtonInfo YesButtonInfo;
	YesButtonInfo.ButtonType = EConfirmationScreenButtonType::Confirm;
	YesButtonInfo.ButtonText = FText::FromString(TEXT("Yes"));

	FConfirmationButtonInfo NoButtonInfo;
	NoButtonInfo.ButtonType = EConfirmationScreenButtonType::Cancel;
	NoButtonInfo.ButtonText = FText::FromString(TEXT("No"));

	auto* ConfirmationScreenObject = NewObject<UConfirmationScreenInfoObject>();
	ConfirmationScreenObject->ConfirmationMessage = InConfirmationMessage;
	ConfirmationScreenObject->ConfirmationTitle = InConfirmationTitle;
	ConfirmationScreenObject->ConfirmationButtons.Add(YesButtonInfo);
	ConfirmationScreenObject->ConfirmationButtons.Add(NoButtonInfo);

	return ConfirmationScreenObject;
}

UConfirmationScreenInfoObject* UConfirmationScreenInfoObject::CreateOkCancelScreenInfo(const FText& InConfirmationTitle,
	const FText& InConfirmationMessage)
{
	FConfirmationButtonInfo OkButtonInfo;
	OkButtonInfo.ButtonType = EConfirmationScreenButtonType::Confirm;
	OkButtonInfo.ButtonText = FText::FromString(TEXT("Ok"));

	FConfirmationButtonInfo CancelButtonInfo;
	CancelButtonInfo.ButtonType = EConfirmationScreenButtonType::Cancel;
	CancelButtonInfo.ButtonText = FText::FromString(TEXT("Cancel"));

	auto* ConfirmationScreenObject = NewObject<UConfirmationScreenInfoObject>();
	ConfirmationScreenObject->ConfirmationMessage = InConfirmationMessage;
	ConfirmationScreenObject->ConfirmationTitle = InConfirmationTitle;
	ConfirmationScreenObject->ConfirmationButtons.Add(OkButtonInfo);
	ConfirmationScreenObject->ConfirmationButtons.Add(CancelButtonInfo);

	return ConfirmationScreenObject;
}

void UFrontendConfirmationWidget::InitConfirmScreen(const UConfirmationScreenInfoObject* InConfirmScreenObject,
                                                    TFunction<void(EConfirmationScreenButtonType)> InClickedCallback)
{
	if (!InConfirmScreenObject)
	{
		return;
	}
	check(!InConfirmScreenObject->ConfirmationButtons.IsEmpty());

	if (ConfirmButtonBox->GetNumEntries() != 0)
	{
		ConfirmButtonBox->Reset<UFrontendCommonButtonBase>([](const UFrontendCommonButtonBase& Widget)
		{
			Widget.OnClicked().Clear();
		});
	}

	TitleTextBlock->SetText(InConfirmScreenObject->ConfirmationTitle);
	MessageTextBlock->SetText(InConfirmScreenObject->ConfirmationMessage);
	for (const auto& [ButtonText, ButtonType] : InConfirmScreenObject->ConfirmationButtons)
	{
		FDataTableRowHandle RowHandle;
		switch (ButtonType)
		{
		case EConfirmationScreenButtonType::Cancel:
			RowHandle = ICommonInputModule::GetSettings().GetDefaultBackAction();
			break;
		case EConfirmationScreenButtonType::Close:
			RowHandle = ICommonInputModule::GetSettings().GetDefaultBackAction();
			break;
		case EConfirmationScreenButtonType::Unknown:
		default:
			break;
		}

		auto* Button = ConfirmButtonBox->CreateEntry<UFrontendCommonButtonBase>();
		Button->SetButtonText(ButtonText);
		Button->SetTriggeringInputAction(RowHandle);
		Button->OnClicked().AddLambda([this, InClickedCallback, ButtonType]()
		{
			InClickedCallback(ButtonType);
			DeactivateWidget();
		});
	}

	ConfirmButtonBox->GetAllEntries().Last()->SetFocus();
}
