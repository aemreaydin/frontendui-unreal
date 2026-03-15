#include "FrontendGameplayTags.h"

namespace FrontendGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG(Frontend_WidgetStack_Modal,
	                       "Frontend.WidgetStack.Modal");
	UE_DEFINE_GAMEPLAY_TAG(Frontend_WidgetStack_GameMenu,
	                       "Frontend.WidgetStack.GameMenu");
	UE_DEFINE_GAMEPLAY_TAG(Frontend_WidgetStack_GameHud,
	                       "Frontend.WidgetStack.GameHud");
	UE_DEFINE_GAMEPLAY_TAG(Frontend_WidgetStack_Frontend,
	                       "Frontend.WidgetStack.Frontend");

	UE_DEFINE_GAMEPLAY_TAG(Frontend_Widget_PressAnyKey, "Frontend.Widget.PressAnyKey");
	UE_DEFINE_GAMEPLAY_TAG(Frontend_Widget_MainMenuScreen, "Frontend.Widget.MainMenuScreen");
	UE_DEFINE_GAMEPLAY_TAG(Frontend_Widget_StoryScreen, "Frontend.Widget.StoryScreen");
	UE_DEFINE_GAMEPLAY_TAG(Frontend_Widget_ConfirmationScreen, "Frontend.Widget.ConfirmationScreen");
} // namespace FrontendGameplayTags
