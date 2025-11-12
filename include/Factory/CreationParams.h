#pragma once
#include <SFML/System/Vector2.hpp>
#include <optional>

class LevelLogicManager;
class TargetingSystem;
class PlayerResourceManager;
class UIManager;
class Board;
class GameObjectManager;

struct CreationParams {
	sf::Vector2f position;
	std::optional<sf::Vector2f> direction;

	LevelLogicManager* levelLogicManager = nullptr;
	TargetingSystem* TargetingSystem = nullptr;
	PlayerResourceManager* PlayerResourceManager = nullptr;
	UIManager* UIManager = nullptr;
	Board* board = nullptr;
	GameObjectManager* objectManager = nullptr;
};