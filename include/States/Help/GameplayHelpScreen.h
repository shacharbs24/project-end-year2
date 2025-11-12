
#pragma once
#include "States/Help/IHelpScreen.h"
#include <SFML/Graphics.hpp>

class GameplayHelpScreen : public IHelpScreen {
public:
    explicit GameplayHelpScreen();

    void handleEvent(const sf::Event&) override {}  
    void draw(sf::RenderWindow& win) const override;

private:
    sf::Sprite m_background;
};