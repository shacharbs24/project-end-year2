#include "States/Trap/ReadyState.h"
#include "GameObject/Plants/TrapPlant.h"

void ReadyState::onEnter(TrapPlant& plant)
{
	plant.setAnimation(plant.getReadyAnimation());
}

std::unique_ptr<ITrapState> ReadyState::update(TrapPlant&, const sf::Time&)
{
	return nullptr;
}

void ReadyState::handleCollision(TrapPlant& plant, Zombie& zombie)
{
	plant.triggerBehavior(zombie);
}