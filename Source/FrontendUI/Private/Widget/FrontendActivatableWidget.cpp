#include "Widget/FrontendActivatableWidget.h"
#include "FrontendPlayerController.h"

AFrontendPlayerController* UFrontendActivatableWidget::GetOwningPlayerController()
{
	CachedPlayerController = GetOwningPlayer<AFrontendPlayerController>();
	return CachedPlayerController;
}
