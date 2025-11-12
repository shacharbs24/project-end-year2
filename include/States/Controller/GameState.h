#pragma once
#include "State.h"
#include "Managers/TextureManager.h"
#include <memory>
#include "Board.h"
#include "Managers/PlayerResourceManager.h"
#include "Managers/LevelLogicManager.h"
#include "Managers/TargetingSystem.h"
#include "UI/UIManager.h"
#include "Managers/GameObjectManager.h"
#include "LevelManagment/LevelScripter.h"

class StateMachine;
class GameObject;

class GameState : public State
{
public:
	GameState(StateMachine& m, int levelNumber);
	void handleEvent(const sf::Event& e) override;
	void update(const sf::Time& dt) override;
	void draw(sf::RenderWindow& win) const override;

private:

	TargetingSystem m_targetingSystem;
	GameObjectManager m_objectManager;
	PlayerResourceManager m_PlayerResourceManager;
	LevelScripter m_scripter;
	LevelLogicManager m_levelLogicManager;
	UIManager m_uiManager;
	Board m_board;

	void checkGameOver();
	void createCallbacks();
};