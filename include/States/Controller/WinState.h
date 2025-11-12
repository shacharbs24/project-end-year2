#pragma once

#include "States/Controller/State.h"
#include "Button/Button.h"
#include <vector>

class WinState : public State
{
public:
	WinState(StateMachine& machine, int levelNum);
	void handleEvent(const sf::Event& event) override;
	void update(const sf::Time&) override {}
	void draw(sf::RenderWindow& win) const override;

private:
	void setUpButtons();
	sf::Sprite m_winSprite;
	sf::Text m_winText;
	sf::RectangleShape m_overlay;
	std::vector<Button> m_buttons;
	int m_levelNum;
};
