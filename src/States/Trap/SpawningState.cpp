#include "States/Trap/SpawningState.h"
#include "States/Trap/ReadyState.h"
#include "GameObject/Plants/TrapPlant.h"
#include "GameObject/Zombies/Zombie.h"

SpawningState::SpawningState(const sf::Time& duration) : m_animationDuration(duration) {}

void SpawningState::onEnter(TrapPlant& plant) 
{
    plant.setAnimation(plant.getSpawningAnimation());
    m_animationClock.restart();
}

std::unique_ptr<ITrapState> SpawningState::update(TrapPlant&, const sf::Time&)
{
    if (m_animationClock.getElapsedTime() >= m_animationDuration)
        return std::make_unique<ReadyState>();
    return nullptr;
}

