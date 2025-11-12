#pragma once

#include "States/Controller/State.h"
#include "Button/Button.h"

class GameOverState : public State
{
public:
	GameOverState(StateMachine& machine, int levelNum);
	void handleEvent(const sf::Event& event) override;
	void update(const sf::Time&) override {};
	void draw(sf::RenderWindow& win) const override;

private:
	sf::RectangleShape m_overlay;
	sf::Text m_gameOverText;
	std::vector<Button> m_buttons;
	int m_levelNum;
	sf::Sprite m_GameOverSprite;
	void setUpButtons();
};
