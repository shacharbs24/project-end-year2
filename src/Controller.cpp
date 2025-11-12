#include "Controller.h"
#include "Config/GameConfig.h"
#include "States/Controller/MenuState.h"
#include <Managers/TextureManager.h>

Controller::Controller() : m_states(m_window)
{
	m_window.create({ window::width, window::height }, "Plants vs. Zombies", sf::Style::Close);
	auto& icon = TextureManager::getInstance().getIcon();
	m_window.setIcon(icon.getSize().x,	icon.getSize().y, icon.getPixelsPtr());

	m_window.setFramerateLimit(60);
	m_states.push<MenuState>();
}

void Controller::run()
{
	sf::Clock clock;
	sf::Time accumulator = sf::Time::Zero;
	while (m_window.isOpen())
	{
		processEvents();

		accumulator += clock.restart();
		while (accumulator >= m_fixedStep)
		{
			update(m_fixedStep);
			accumulator -= m_fixedStep;
		}
		render();
	}
}

void Controller::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window.close();
		m_states.handleEvent(event);
	}
}

void Controller::update(const sf::Time dt)
{
	m_states.update(dt);
}

void Controller::render()
{
	m_window.clear(sf::Color::Black);
	m_states.draw(m_window);
	m_window.display();
}


