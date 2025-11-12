#include "States/Zombie/WalkingState.h"
#include "GameObject/Zombies/Zombie.h"
#include "Strategy/Movement/IMovementStrategy.h"
#include <States/Zombie/EatingState.h>
#include "GameObject/Plants/Plant.h"

void WalkingState::onEnter(Zombie& zombie)
{
	zombie.setAnimation(zombie.getWalkAnimation());
}

std::unique_ptr<IZombieState> WalkingState::update(Zombie& zombie, const sf::Time& dt)
{
	zombie.move(dt);
	zombie.attemptShooting(dt);
	return nullptr;
}

std::unique_ptr<IZombieState> WalkingState::onCollision(Zombie& zombie, Plant* plant)
{
	zombie.setEatingTarget(plant);
	if (plant) plant->addObserver(&zombie);
	return std::make_unique<EatingState>();
}