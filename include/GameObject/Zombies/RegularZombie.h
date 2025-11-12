#pragma once
#include "GameObject/Zombies/Zombie.h"
#include "Utiles.h"

class RegularZombie : public Zombie
{
public:
	RegularZombie(const CreationParams& p, const ZombieData::Definition& def,
		std::unique_ptr<IMovementStrategy> moveStrategy, std::unique_ptr<ITrapResponseStrategy> trapResponseStrategy);
};