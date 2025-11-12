#pragma once
#include "ICommand.h"

class HelpState;
enum class HelpScreen;

class SwitchHelpScreenCommand : public ICommand {
public:
    SwitchHelpScreenCommand(HelpState& helpState, HelpScreen screen);
    void execute() override;

private:
    HelpState& m_helpState;
    HelpScreen m_screen;
};