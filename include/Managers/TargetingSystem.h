#pragma once
#include <array>
#include <list>

#include "GameObject/GameObject.h"
#include "Board.h"

class Plant;
class Zombie;

class TargetingSystem
{
public:
	using ObjectList = std::list<const GameObject*>;
	using TargetGrid = std::array<ObjectList, Board::ROWS>;

	void addPlant(const Plant& plant);
	void removePlant(const Plant& plant);
	void addZombie(const Zombie& zombie);
	void removeZombie(const Zombie& zombie);

	bool hasZombieInFront(const Plant& plant) const;
	bool hasZombieBehind(const Plant& plant) const;
	bool hasPlantInFront(const Zombie& zombie) const;

	bool anyZombiesLeft() const;
private:

	template <typename SourceT, typename ComparatorT>
	bool findTarget(const SourceT& source, const ObjectList& targets, ComparatorT comp) const;

	TargetGrid m_plants;
	TargetGrid m_zombies;
};

template <typename SourceT, typename ComparatorT>
bool TargetingSystem::findTarget(const SourceT& source, const ObjectList& targets, ComparatorT comp) const
{
	const sf::Vector2f sourcePos = source.getCenter();
	for (const GameObject* targetPtr : targets)
		if (comp(targetPtr->getCenter().x, sourcePos.x))
			return true;
	return false;
}
