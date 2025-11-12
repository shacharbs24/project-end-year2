#pragma once
#include "States/Controller/State.h"
#include "Button/Button.h"
#include <vector>

class StateMachine;

class PauseState : public State
{
public:
	PauseState(StateMachine& m, int level);
	void handleEvent(const sf::Event& e) override;
	void update(const sf::Time&) override {};
	void draw(sf::RenderWindow& win) const override;

private:
	void setupUI();
	void createButton(const std::string& label, std::unique_ptr<ICommand> command, const sf::Vector2f& position);

	sf::RectangleShape m_background;
	sf::Text m_pausedText;
	std::vector<Button> m_buttons;
	int m_level;
	sf::Font& m_font;
};