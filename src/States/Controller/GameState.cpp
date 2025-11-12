#include "Managers/AudioManager.h"
#include "States/Controller/GameState.h"
#include "States/Controller/StateMachine.h"
#include "States/Controller/WinState.h"
#include <LevelManagment/LevelManager.h>
#include <States/Controller/GameOverState.h>

GameState::GameState(StateMachine& m, int levelNumber) :
	State(m),
	m_objectManager(),
	m_targetingSystem(),
	m_PlayerResourceManager(),
	m_scripter(m_levelLogicManager, m_uiManager, levelNumber),
	m_levelLogicManager(m_uiManager, m_PlayerResourceManager, m_scripter, levelNumber),
	m_uiManager(m_PlayerResourceManager, m_machine, m_levelLogicManager, m_objectManager),
	m_board(m_uiManager, m_PlayerResourceManager)
{
	createCallbacks();
	AudioManager::getInstance().playMusic("Grasswalk");
}

void GameState::draw(sf::RenderWindow& win) const
{
	m_uiManager.draw(win);
	m_objectManager.draw(win);
	m_uiManager.drawText(win);
}

void GameState::update(const sf::Time& dt)
{
	m_scripter.update(dt);
	m_uiManager.update(dt);
	m_objectManager.update(dt);
	m_levelLogicManager.update(dt);
	checkGameOver();
}

void GameState::handleEvent(const sf::Event& e)
{
	m_board.handleEvent(e);
	m_uiManager.handleEvent(e);
	m_objectManager.handleEvent(e);
}

void GameState::checkGameOver()
{
	if (m_levelLogicManager.isGameOver())
		m_machine.push<GameOverState>(m_levelLogicManager.getLevel());
	

	if (m_levelLogicManager.getWin())
	{
		LevelManager::getInstance().unlockNextLevel(m_levelLogicManager.getLevel());
		m_machine.push<WinState>(m_levelLogicManager.getLevel());
	}
}

void GameState::createCallbacks()
{
	m_board.onAddPlant = [this](const sf::Vector2f& pos, const std::string& id) {
		CreationParams params = { .position = pos, .TargetingSystem = &m_targetingSystem, .PlayerResourceManager = &m_PlayerResourceManager,
			.UIManager = &m_uiManager, .board = &m_board , .objectManager = &m_objectManager };
		m_objectManager.addObject(std::move(Factory::create(id, params)));
		};;

	m_levelLogicManager.onAddZombie = [this](const sf::Vector2f& pos, const std::string& id) {
		CreationParams params = { .position = pos,.levelLogicManager = &m_levelLogicManager ,.TargetingSystem = &m_targetingSystem,
			.objectManager = &m_objectManager };
		m_objectManager.addObject(std::move(Factory::create(id, params)));
		};;

	m_levelLogicManager.onAddSun = [this](const sf::Vector2f& pos, const std::string& id) {
		CreationParams params = { .position = pos, .PlayerResourceManager = &m_PlayerResourceManager };
		m_objectManager.addObject(std::move(Factory::create(id, params)));
		};;

	m_levelLogicManager.onAddGift = [this](const sf::Vector2f& pos, const std::string& id)
		{
			CreationParams params = { .position = pos,.PlayerResourceManager = &m_PlayerResourceManager,.UIManager = &m_uiManager,
				.objectManager = &m_objectManager
			};
			m_objectManager.addObject(Factory::create(id, params));
		};
}