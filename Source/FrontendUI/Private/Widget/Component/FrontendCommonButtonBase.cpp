#include "Widget/Component/FrontendCommonButtonBase.h"
#include "CommonTextBlock.h"
#include "FrontendUISubsystem.h"

void UFrontendCommonButtonBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (ButtonTextBlock && !ButtonDisplayText.IsEmptyOrWhitespace())
	{
		SetButtonText(ButtonDisplayText);
	}
}

void UFrontendCommonButtonBase::NativeOnCurrentTextStyleChanged()
{
	Super::NativeOnCurrentTextStyleChanged();

	if (ButtonTextBlock && GetCurrentTextStyleClass())
	{
		ButtonTextBlock->SetStyle(GetCurrentTextStyleClass());
	}
}

void UFrontendCommonButtonBase::NativeOnHovered()
{
	Super::NativeOnHovered();

	if (!ButtonDescriptionText.IsEmptyOrWhitespace())
	{
		UFrontendUISubsystem::Get(this)->OnButtonHoveredUpdateDescription.Broadcast(this, ButtonDescriptionText);
	}
}

void UFrontendCommonButtonBase::NativeOnUnhovered()
{
	Super::NativeOnUnhovered();

	if (!ButtonDescriptionText.IsEmptyOrWhitespace())
	{
		UFrontendUISubsystem::Get(this)->OnButtonHoveredUpdateDescription.Broadcast(this, FText::GetEmpty());
	}
}

void UFrontendCommonButtonBase::SetButtonText(const FText Text) const
{
	ButtonTextBlock->SetText(bIsTextUpperCase ? Text.ToUpper() : Text);
}
