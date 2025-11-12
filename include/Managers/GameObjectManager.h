#pragma once
#include <list>
#include <memory>
#include <SFML/Graphics.hpp>
#include "GameObject/GameObject.h"
#include "CollisionHandler.h"
#include <functional>
#include <array>
#include "Board.h"
#include <random>

class GameState;

class GameObjectManager {
public:
	explicit GameObjectManager();

	void addObject(std::unique_ptr<GameObject> obj);
	void update(const sf::Time& dt);
	void draw(sf::RenderWindow& window) const;
	void handleEvent(const sf::Event& event);
	
	template <typename Func>
	void forEachInRows(Func&& action);
	template <typename Func>
	void forEachInRows(Func&& action) const;

private:
	void checkCollisions();
	void cleanupObjects();

	std::array<std::list<std::unique_ptr<GameObject>>, Board::ROWS> m_rows;
	std::mt19937 m_rng;
};



template<typename Func>
inline void GameObjectManager::forEachInRows(Func&& action)
{
	for (auto& bucket : m_rows) 
	{
		for (auto& obj : bucket) 
		{
			if (obj) action(*obj);
		}
	}
}

template<typename Func>
inline void GameObjectManager::forEachInRows(Func&& action) const
{
	for (const auto& bucket : m_rows)
	{
		for (const auto& obj : bucket)
		{
			if (obj) action(*obj);
		}
	}
}
