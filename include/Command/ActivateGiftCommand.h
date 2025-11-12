#pragma once
#include "Command/Icommand.h"
#include <string>

class UIManager;
class Button; 
class GiftBar;

class ActivateGiftCommand : public ICommand {
public:
    ActivateGiftCommand(GiftBar& gb,const std::string& giftType);
    void execute() override;

private:
    GiftBar& m_giftBar;
    std::string m_giftTypeID;
};