#include "States/Controller/GameOverState.h"
#include "States/Controller/StateMachine.h"
#include "Managers/TextureManager.h"
#include "Command/PushStateCommand.h"
#include "States/Controller/MenuState.h"
#include "States/Controller/GameState.h"
#include "Command/RestartLevelCommand.h"
#include "Command/PopStateCommand.h"
#include "Managers/AudioManager.h"
#include "Config/GameConfig.h"

GameOverState::GameOverState(StateMachine& machine, int levelNum) :
	State(machine), m_levelNum(levelNum),
	m_GameOverSprite(TextureManager::getInstance().getTexture("GameOverScreen"))
{
	m_overlay.setSize({ (float)window::width, (float)window::height });
	m_overlay.setFillColor(sf::Color(0, 0, 0, 150));

	m_gameOverText.setFont(TextureManager::getInstance().getFont("font"));

	sf::FloatRect spriteBounds = m_GameOverSprite.getLocalBounds();
	m_GameOverSprite.setOrigin(spriteBounds.width / 2.f, spriteBounds.height / 2.f);
	m_GameOverSprite.setPosition((float)window::width / 2.f, (float)window::height / 2.f - 100.f);
	AudioManager::getInstance().playMusic("losemusic", false);
	setUpButtons();
}

void GameOverState::handleEvent(const sf::Event& e)
{
	if (e.type == sf::Event::MouseMoved)
	{
		sf::Vector2f mousePos(float(e.mouseMove.x), float(e.mouseMove.y));
		for (auto& button : m_buttons)
		{
			button.handleHover(mousePos);
		}
	}

	for (auto& b : m_buttons)
	{
		b.handleEvent(e);
	}
}

void GameOverState::draw(sf::RenderWindow& win) const
{
	m_machine.drawPrevState(win);
	win.draw(m_overlay);
	win.draw(m_GameOverSprite);
	for (const auto& button : m_buttons)
	{
		button.draw(win);
	}
}

void GameOverState::setUpButtons()
{
	auto restartCmd = std::make_unique<RestartLevelCommand>(m_machine, m_levelNum);
	auto levelSelectCmd = std::make_unique<PopStateCommand>(m_machine, 2);

	m_buttons.emplace_back(Button({ 580, 455 }, { 200, 45 }, "Try Again", 30, std::move(restartCmd)));
	m_buttons.emplace_back(Button({ 820 , 455 }, { 200,45 }, "Level Menu", 30, std::move(levelSelectCmd)));
}