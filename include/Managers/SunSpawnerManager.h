#pragma once

#include <SFML/System/Clock.hpp>
#include <random>
#include <functional>
#include <SFML/System/Vector2.hpp>

class GameState;

class SunSpawnerManager
{
public:
	explicit SunSpawnerManager();
	void update(const sf::Time&);
	std::function<void(const sf::Vector2f&, const std::string&)> onAddObj;

private:
	void spawnSunFromSky();

	sf::Clock m_sunSpawnClock;
	sf::Time m_nextSunSpawnTime;
	std::mt19937 m_rng;
};