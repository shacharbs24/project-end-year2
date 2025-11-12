#pragma once
#include "States/Help/IHelpScreen.h"
#include "Button/Button.h"
#include <vector>


class HelpState;

class AlmanacScreen : public IHelpScreen 
{
public:
    explicit AlmanacScreen(HelpState& owner);   

    void handleEvent(const sf::Event& e) override;
    void draw(sf::RenderWindow& win) const override;


private:
    void setup();
	HelpState& m_owner;
    sf::Sprite m_background;
    std::vector<Button> m_categoryButtons;
};