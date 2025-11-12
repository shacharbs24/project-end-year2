#pragma once
#include "ICommand.h"
class Button;

class MuteCommand : public ICommand {
public:
    MuteCommand(Button& btn);
    void execute() override;

private:
    Button& m_button;
};