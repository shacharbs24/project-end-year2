#include "States/Help/GameplayHelpScreen.h"
#include "Managers/TextureManager.h"

GameplayHelpScreen::GameplayHelpScreen() 
{
    m_background.setTexture(TextureManager::getInstance().getTexture("gameplay_help"));
}

void GameplayHelpScreen::draw(sf::RenderWindow& win) const
{
    win.draw(m_background);
}