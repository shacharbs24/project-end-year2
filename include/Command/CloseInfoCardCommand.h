#pragma once
#include "ICommand.h"
#include "States/Controller/HelpState.h"

class CloseInfoCardCommand : public ICommand {
public:
    CloseInfoCardCommand(IHelpScreen& s) : m_helpState(s) {}
    void execute() override { m_helpState.clearSelection();}
private:
    IHelpScreen& m_helpState;
};