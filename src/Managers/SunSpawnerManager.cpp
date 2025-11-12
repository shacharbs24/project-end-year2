#include "Managers/SunSpawnerManager.h"
#include "States/Controller/GameState.h"
#include <random>
#include "Factory/Factory.h"
#include "Config/GameConfig.h"

SunSpawnerManager::SunSpawnerManager()
	: m_rng(std::random_device{}()), m_nextSunSpawnTime(sf::seconds(float(5 + m_rng() % 5)))
{}

void SunSpawnerManager::update(const sf::Time&)
{
	if (m_sunSpawnClock.getElapsedTime() >= m_nextSunSpawnTime)
	{
		spawnSunFromSky();
		m_sunSpawnClock.restart();
		m_nextSunSpawnTime = sf::seconds(8.f + float(m_rng() % 7));
	}
}

void SunSpawnerManager::spawnSunFromSky()
{
	float randomX = 150.f + (m_rng() % (window::width - 300));
	onAddObj({ randomX, -50.f }, "falling_sun");
}