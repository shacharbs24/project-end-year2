#pragma once
#include "GameObject/Zombies/Zombie.h"
#include "ShootingLogicHandler.h"

class ShootingZombie : public Zombie, public ShootingLogicHandler
{
public:
	ShootingZombie(const CreationParams& p, const ZombieData::ShootingZombieDef& def,
		std::unique_ptr<IMovementStrategy> moveStrategy,
		std::unique_ptr<IShootStrategy> shootStrategy);

	void attemptShooting(const sf::Time& dt) override;
};