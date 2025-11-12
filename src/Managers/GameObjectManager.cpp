#include "Managers/GameObjectManager.h"
#include "States/Controller/GameState.h"
#include <iostream>
#include "Logger.h"

GameObjectManager::GameObjectManager() : m_rng(std::random_device{}())
{
}

void GameObjectManager::addObject(std::unique_ptr<GameObject> obj)
{
	int row = obj->getGridRow();
	if (row < 0 || row >= Board::ROWS)
		row = std::uniform_int_distribution<int>(0, Board::ROWS - 1)(m_rng);
	m_rows[row].push_back(std::move(obj));
}

void GameObjectManager::handleEvent(const sf::Event& event)
{
	forEachInRows([&event](GameObject& obj) {obj.handleEvent(event); });
}

void GameObjectManager::update(const sf::Time& dt)
{
	forEachInRows([&dt](GameObject& obj) {obj.update(dt); });
	checkCollisions();
	cleanupObjects();
}

void GameObjectManager::draw(sf::RenderWindow& window) const
{
	forEachInRows([&window](GameObject& obj) {obj.draw(window); });
}

void GameObjectManager::checkCollisions()
{
	for (auto& bucket : m_rows)
	{
		for (auto it1 = bucket.begin(); it1 != bucket.end(); ++it1)
		{
			if ((*it1)->isToDelete() || !(*it1)->isCollidable()) continue;

			for (auto it2 = std::next(it1); it2 != bucket.end(); ++it2)
			{
				if ((*it2)->isToDelete() || !(*it2)->isCollidable()) continue;

				if ((*it1)->getGlobalBounds().intersects((*it2)->getGlobalBounds()))
				{
					try
					{
						processCollision(**it1, **it2);
					}
					catch (const UnknownCollision& e)
					{
						Logger::getInstance().logError(e.what());
					}
				}
			}
		}
	}
}

void GameObjectManager::cleanupObjects()
{
	for (auto& bucket : m_rows)
	{
		bucket.remove_if(
			[](const std::unique_ptr<GameObject>& obj)
			{ return obj->isToDelete(); });
	}
}