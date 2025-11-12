#include "States/Controller/WinState.h"
#include "Managers/TextureManager.h"
#include "Command/RestartLevelCommand.h"
#include "Command/PopStateCommand.h"
#include "Managers/AudioManager.h"
#include "Config/GameConfig.h"

WinState::WinState(StateMachine& machine, int levelNum)
	: State(machine), m_levelNum(levelNum),
	m_winSprite(TextureManager::getInstance().getTexture("Winscreen"))
{
	m_overlay.setSize({ (float)window::width, (float)window::height });
	m_overlay.setFillColor(sf::Color(0, 0, 0, 150));
	m_winText.setFont(TextureManager::getInstance().getFont("font"));

	sf::FloatRect spriteBounds = m_winSprite.getLocalBounds();
	m_winSprite.setOrigin(spriteBounds.width / 2.f, spriteBounds.height / 2.f);
	m_winSprite.setPosition((float)window::width / 2.f, (float)window::height / 2.f - 100.f);
	AudioManager::getInstance().playMusic("winmusic", false);
	setUpButtons();
}

void WinState::handleEvent(const sf::Event& e)
{
	if (e.type == sf::Event::MouseMoved)
	{
		for (auto& button : m_buttons)
		{
			button.handleHover({ float(e.mouseMove.x), float(e.mouseMove.y) });
		}
	}
	for (auto& b : m_buttons)
	{
		b.handleEvent(e);
	}
}

void WinState::draw(sf::RenderWindow& win) const
{
	m_machine.drawPrevState(win);
	win.draw(m_overlay);
	win.draw(m_winSprite);
	for (const auto& button : m_buttons)
	{
		button.draw(win);
	}
}

void WinState::setUpButtons()
{
	auto Playagaincmd = std::make_unique<RestartLevelCommand>(m_machine, m_levelNum);
	auto nextLevelCmd = std::make_unique<RestartLevelCommand>(m_machine, m_levelNum + 1);
	auto levelSelectCmd = std::make_unique<PopStateCommand>(m_machine, 2);

	m_buttons.emplace_back(
		Button({ 540, 450 }, { 200, 45 }, "Next Level", 25, std::move(nextLevelCmd)));

	m_buttons.emplace_back(
		Button({ 705, 450 }, { 200, 45 }, "Level Menu", 25, std::move(levelSelectCmd)));

	m_buttons.emplace_back(
		Button({ 870, 450 }, { 200, 45 }, "Play Again", 25, std::move(Playagaincmd)));
}