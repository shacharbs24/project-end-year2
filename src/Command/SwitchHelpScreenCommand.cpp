#include "Command/SwitchHelpScreenCommand.h"
#include "States/Controller/HelpState.h"

SwitchHelpScreenCommand::SwitchHelpScreenCommand(HelpState& helpState, HelpScreen screen)
    : m_helpState(helpState), m_screen(screen)
{}

void SwitchHelpScreenCommand::execute()
{
    m_helpState.switchToScreen(m_screen);
}