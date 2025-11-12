#include "Command/MuteCommand.h"
#include "Managers/AudioManager.h"
#include "Button/Button.h"

MuteCommand::MuteCommand(Button& button) : m_button(button) 
{}

void MuteCommand::execute()
{
    auto& aud = AudioManager::getInstance();
    aud.toggleMute();
    m_button.setTextureRect(aud.isMuted() ? sf::IntRect(486, 161, 53, 51) : sf::IntRect(551, 161, 53, 51));
}