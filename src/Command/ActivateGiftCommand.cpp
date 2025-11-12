#include "Command/ActivateGiftCommand.h"
#include "UI/GiftBar.h"
#include <iostream>

ActivateGiftCommand::ActivateGiftCommand(GiftBar& gb, const std::string& giftType)
    : m_giftBar(gb), m_giftTypeID(giftType) {}

void ActivateGiftCommand::execute() 
{
    m_giftBar.activateGift(m_giftTypeID);
}