#include "States/Help/GiftHelpScreen.h"

GiftHelpScreen::GiftHelpScreen(StateMachine& machine)
	: AlmanacHelpScreen(machine, GIFT_CARDS, "gift_bar", "gifts_help_cards", "Gifts : click for info", "gift_screen")
{
}