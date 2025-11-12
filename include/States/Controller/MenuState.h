#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"

class Button;
class StateMachine;

class MenuState : public State
{
public:
	MenuState(StateMachine& m);
	virtual void handleEvent(const sf::Event& e) override;
	virtual void draw(sf::RenderWindow& win) const override;
	virtual void update(const sf::Time&) override {};

private:
	sf::Sprite m_backgroundSprite;
	std::vector<Button> m_buttons;
	void setupButtons();
};