#include "States/Help/AlmanacScreen.h"
#include "Managers/TextureManager.h"
#include "Command/SwitchHelpScreenCommand.h"
 #include <States/Help/PlantsHelpScreen.h>
 #include <States/Help/ZombiesHelpScreen.h>
 #include <States/Help/GiftHelpScreen.h>
 #include "States/Controller/HelpState.h"



AlmanacScreen::AlmanacScreen(HelpState& owner)
    : m_owner(owner)                           
{
    m_background.setTexture(
        TextureManager::getInstance().getTexture("almanac_screen"));
    setup();
}

void AlmanacScreen::setup() 
{
    m_categoryButtons.clear();


    m_categoryButtons.emplace_back(
        sf::Vector2f{ 80.f, 220.f },
        sf::Vector2f{ 390.f, 390.f },
        "",
        0,
        std::make_unique<SwitchHelpScreenCommand>(m_owner, HelpScreen::PLANTS)
    );


    m_categoryButtons.emplace_back(
        sf::Vector2f{ 570.f, 220.f },
        sf::Vector2f{ 390.f, 390.f },
        "",
        0,
        std::make_unique<SwitchHelpScreenCommand>(m_owner, HelpScreen::GIFTS)
    );


    m_categoryButtons.emplace_back(
        sf::Vector2f{ 1070.f, 220.f },
        sf::Vector2f{ 390.f, 390.f },
        "",
        0,
        std::make_unique<SwitchHelpScreenCommand>(m_owner, HelpScreen::ZOMBIES)
    );
}


void AlmanacScreen::handleEvent(const sf::Event& e) 
{
    for (auto& button : m_categoryButtons) 
    {
        button.handleEvent(e);
    }
}

void AlmanacScreen::draw(sf::RenderWindow& win) const
{
    win.draw(m_background);

    for (const auto& btn : m_categoryButtons)
        btn.draw(win);
}
