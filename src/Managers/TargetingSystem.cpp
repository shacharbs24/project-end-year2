#include "Managers/TargetingSystem.h"
#include "GameObject/GameObject.h"
#include "GameObject/Plants/Plant.h"
#include "GameObject/Zombies/Zombie.h"

void TargetingSystem::addPlant(const Plant& plant)
{
	const int row = Board::pixelToGrid(plant.getCenter()).y;
	m_plants[row].push_back(&plant);
}

void TargetingSystem::removePlant(const Plant& plant)
{
	const int row = Board::pixelToGrid(plant.getCenter()).y;
	m_plants[row].remove(&plant);
}

void TargetingSystem::addZombie(const Zombie& zombie)
{
	const int row = Board::pixelToGrid(zombie.getCenter()).y;
	m_zombies[row].push_back(&zombie);
}

void TargetingSystem::removeZombie(const Zombie& zombie)
{
	const int row = Board::pixelToGrid(zombie.getCenter()).y;
	m_zombies[row].remove(&zombie);
}

bool TargetingSystem::hasZombieInFront(const Plant& plant) const {
	const int row = Board::pixelToGrid(plant.getCenter()).y;
	auto isInFront = [](float targetX, float sourceX) { return targetX > sourceX; };
	return findTarget(plant, m_zombies[row], isInFront);
}

bool TargetingSystem::hasZombieBehind(const Plant& plant) const
{
	const int row = Board::pixelToGrid(plant.getCenter()).y;
	auto isInFront = [](float targetX, float sourceX) { return targetX < sourceX; };
	return findTarget(plant, m_zombies[row], isInFront);
}

bool TargetingSystem::hasPlantInFront(const Zombie& zombie) const {
	const int row = Board::pixelToGrid(zombie.getCenter()).y;
	auto isInFront = [](float targetX, float sourceX) { return targetX < sourceX; };
	return findTarget(zombie, m_plants[row], isInFront);
}

bool TargetingSystem::anyZombiesLeft() const
{
	for (const auto& row : m_zombies)
		if (!row.empty())
			return true;
	return false;
}