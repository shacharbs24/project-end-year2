#pragma once
#include "Strategy/Shoot/IShootStrategy.h"
#include <memory>
#include <SFML/System.hpp>

class GameObjectManager;

class ShootingLogicHandler
{
public:
	virtual ~ShootingLogicHandler() = default;
	void setObjectManager(GameObjectManager* gameObjectManager) { m_gameObjectManager = gameObjectManager; }

protected:
	std::unique_ptr<IShootStrategy> m_shootStrategy;
	sf::Clock m_shootClock;
	sf::Time m_shootCooldown;
	bool m_isShooting = false;

	void handleShootingUpdate(const sf::Time& dt, const sf::Sprite& sprite, sf::Vector2f shootDirection, sf::Vector2f bulletOffset);
	float m_cooldownMultipler = 1;
private:
	GameObjectManager* m_gameObjectManager;
	bool m_hasFiredOnce = false;
};