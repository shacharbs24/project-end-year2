#include "States/Help/PlantsHelpScreen.h"

PlantsHelpScreen::PlantsHelpScreen(StateMachine& machine)
    : AlmanacHelpScreen(machine, PLANT_CARDS, "plants_bar", "plants_help_cards", "Plants : click for info", "plants_screen")
{
}