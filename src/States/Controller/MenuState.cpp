#include "States/Controller/MenuState.h"
#include "States/Controller/StateMachine.h"
#include "Managers/TextureManager.h"
#include "Button/Button.h"
#include "States/Controller/LevelSelectionState.h"
#include <Command/PushStateCommand.h>
#include <Command/ExitCommand.h>
#include "States/Controller/HelpState.h"
#include "Managers/AudioManager.h"

MenuState::MenuState(StateMachine& m) : State(m)
{
	m_backgroundSprite.setTexture(TextureManager::getInstance().getTexture("menu"));
	setupButtons();
	AudioManager::getInstance().playMusic("intro");
}

void MenuState::handleEvent(const sf::Event& e)
{
	if (e.type == sf::Event::MouseMoved)
	{
		for (auto& b : m_buttons)
		{
			b.handleHover({ float(e.mouseMove.x), float(e.mouseMove.y) });
		}
	}

	for (auto& b : m_buttons)
	{
		b.handleEvent(e);
	}
}

void MenuState::draw(sf::RenderWindow& win) const
{
	win.draw(m_backgroundSprite);

	for (const auto& button : m_buttons)
	{
		button.draw(win);
	}
}

void MenuState::setupButtons()
{
	m_buttons.emplace_back(Button({ 640,410 }, { 310,80 }, "Play", 50, std::make_unique<PushStateCommand<LevelSelectionState>>(m_machine)));
	m_buttons.emplace_back(Button({ 660,530 }, { 280,70 }, "Help", 50, std::make_unique<PushStateCommand<HelpState>>(m_machine)));
	m_buttons.emplace_back(Button({ 670,640 }, { 250,60 }, "Exit", 50, std::make_unique<ExitCommand>(m_machine.getWindow())));
}