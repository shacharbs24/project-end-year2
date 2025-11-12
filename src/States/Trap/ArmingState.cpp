#include "States/Trap/ArmingState.h"
#include "GameObject/Plants/TrapPlant.h"
#include "GameObject/Zombies/Zombie.h"
#include <States/Trap/SpawningState.h>

ArmingState::ArmingState(sf::Time armingTime) : m_armingTime(armingTime) {}


void ArmingState::onEnter(TrapPlant& plant) 
{
    plant.setAnimation(nullptr);
    plant.setSpriteRect({ 1, 35, 30, 22 });
    m_armingClock.restart();
}

std::unique_ptr<ITrapState> ArmingState::update(TrapPlant&, const sf::Time& ) 
{
    if (m_armingClock.getElapsedTime() >= m_armingTime) 
        return std::make_unique<SpawningState>();
    return nullptr;
}

void ArmingState::handleCollision(TrapPlant& plant, Zombie& zombie) 
{
    zombie.onCollisionWithPlant(&plant);
}