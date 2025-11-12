#pragma once
#include "ICommand.h"

class IHelpScreen;

class SelectAlmanacCommand : public ICommand {
public:
    SelectAlmanacCommand(IHelpScreen& help, int i);
    void execute() override;

private:
    IHelpScreen& m_help;
    int m_i;
};