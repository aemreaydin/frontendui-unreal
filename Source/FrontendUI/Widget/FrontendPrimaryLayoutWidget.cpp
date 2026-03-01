#include "FrontendPrimaryLayoutWidget.h"

void UFrontendPrimaryLayoutWidget::PushWidget(const FGameplayTag WidgetTag,
                                              UCommonActivatableWidgetContainerBase* Widget)
{
	if (IsDesignTime())
	{
		return;
	}
	if (WidgetStack.Contains(WidgetTag))
	{
		return;
	}

	WidgetStack.Add(WidgetTag, Widget);
}

UCommonActivatableWidgetContainerBase* UFrontendPrimaryLayoutWidget::GetWidgetByTag(const FGameplayTag WidgetTag) const
{
	checkf(WidgetStack.Contains(WidgetTag), TEXT("Unable to find a widget by the tag %s"), *WidgetTag.ToString());
	return WidgetStack[WidgetTag];
}
