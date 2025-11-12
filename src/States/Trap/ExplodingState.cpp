#include "States/Trap/ExplodingState.h"
#include "GameObject/Plants/TrapPlant.h"

ExplodingState::ExplodingState(sf::Time animationDuration)
    : m_animationDuration(animationDuration) 
{
}

void ExplodingState::onEnter(TrapPlant& plant)
{
    plant.setAnimation(plant.getExplosionAnimation());
    plant.move({ -60.f, -70.f });
    m_animationClock.restart();
}

std::unique_ptr<ITrapState> ExplodingState::update(TrapPlant& plant, const sf::Time&)
{
    if (m_animationClock.getElapsedTime() >= m_animationDuration)
        plant.die();
    return nullptr; 
}

