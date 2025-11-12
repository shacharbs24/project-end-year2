#pragma once
#include "State.h"
#include "Button/Button.h"

class StateMachine;

class LevelSelectionState : public State {
public:
	LevelSelectionState(StateMachine& m);
	virtual void handleEvent(const sf::Event& e) override;
	virtual void update(const sf::Time&) override;
	virtual void draw(sf::RenderWindow& win) const override;

private:
	void syncLevelButtons();
	sf::Sprite m_backgroundSprite;
	std::vector<Button> m_levelButtons;
	Button& m_backButton;
	void createLevelButton(int levelNumber);
};