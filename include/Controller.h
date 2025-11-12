#pragma once
#include<SFML/Graphics.hpp>
#include <States/Controller/StateMachine.h>

class Controller {
public:
	Controller();
	void run();

private:
	sf::RenderWindow m_window;
	StateMachine m_states;
	const sf::Time m_fixedStep = sf::seconds(1.f / 60.f);

	void processEvents();
	void update(const sf::Time dt);
	void render();
};