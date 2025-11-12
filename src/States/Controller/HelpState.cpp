#include "States/Controller/HelpState.h"
#include "Command/PopStateCommand.h"
#include "Command/SwitchHelpScreenCommand.h"
#include <States/Help/GameplayHelpScreen.h>
#include <States/Help/AlmanacScreen.h>
#include <States/Help/PlantsHelpScreen.h>
#include <States/Help/ZombiesHelpScreen.h>
#include <States/Help/GiftHelpScreen.h>
#include <States/Help/MainHelpScreen.h>

const std::unordered_map<HelpScreen, HelpState::ScreenFactory>& HelpState::getScreenFactories()
{
	static const std::unordered_map<HelpScreen, ScreenFactory> factories = {
		{ HelpScreen::MAIN,     { [](HelpState& hs) { return std::make_unique<MainHelpScreen>(hs);                 }, HelpScreen::MAIN      } },
		{ HelpScreen::GAMEPLAY, { [](HelpState&)    { return std::make_unique<GameplayHelpScreen>();               }, HelpScreen::MAIN      } },
		{ HelpScreen::ALMANAC,  { [](HelpState& hs) { return std::make_unique<AlmanacScreen>(hs);                  }, HelpScreen::MAIN      } },
		{ HelpScreen::PLANTS,   { [](HelpState& hs) { return std::make_unique<PlantsHelpScreen>(hs.m_machine);     }, HelpScreen::ALMANAC   } },
		{ HelpScreen::ZOMBIES,  { [](HelpState& hs) { return std::make_unique<ZombiesHelpScreen>(hs.m_machine);    }, HelpScreen::ALMANAC   } },
		{ HelpScreen::GIFTS,    { [](HelpState& hs) { return std::make_unique<GiftHelpScreen>(hs.m_machine);       }, HelpScreen::ALMANAC   } }
	};
	return factories;
}

HelpState::HelpState(StateMachine& machine)
	: State(machine)
	, m_currentScreen(HelpScreen::MAIN)
	, m_backButton(machine.getBackButton())
{
	m_backButton.setCommand(std::make_unique<PopStateCommand>(m_machine));
	switchToScreen(HelpScreen::MAIN);
}

void HelpState::switchToScreen(HelpScreen screen)
{
	m_currentScreen = screen;

	const auto& factories = getScreenFactories();
	const auto it = factories.find(screen);
	if (it == factories.end()) return;

	const auto& factory = it->second;
	m_screenHandler = factory.create(*this);

	if (screen == HelpScreen::MAIN)
		m_backButton.setCommand(std::make_unique<PopStateCommand>(m_machine));
	else
		m_backButton.setCommand(std::make_unique<SwitchHelpScreenCommand>(*this, factory.backTarget));
}

void HelpState::handleEvent(const sf::Event& e)
{
	if (e.type == sf::Event::MouseMoved)
	{
		m_backButton.handleHover({ float(e.mouseMove.x), float(e.mouseMove.y) });
	}
	if (m_screenHandler) m_screenHandler->handleEvent(e);
	m_backButton.handleEvent(e);
}

void HelpState::draw(sf::RenderWindow& win) const
{
	if (m_screenHandler)
		m_screenHandler->draw(win);

	m_backButton.draw(win);
}