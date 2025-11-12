#include "States/Help/ZombiesHelpScreen.h"

ZombiesHelpScreen::ZombiesHelpScreen(StateMachine& machine)
    : AlmanacHelpScreen(machine, ZOMBIE_CARDS, "zombies_bar", "zombie_help_cards", "Zombies : click for info","zombies_screen")
{}