#pragma once

#include "IHelpScreen.h"
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include "Button/Button.h"

class HelpState; 

class MainHelpScreen : public IHelpScreen {
public:
    explicit MainHelpScreen(HelpState& helpState);
    ~MainHelpScreen() override = default;

    void select(int) override {}
    void clearSelection() override {}

    void handleEvent(const sf::Event& e) override;
    void draw(sf::RenderWindow& win) const override;

private:
     void setup();

    HelpState& m_helpState;
    sf::Sprite m_background;
    std::vector<Button> m_buttons;
};
