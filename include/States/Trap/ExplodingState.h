#pragma once
#include "States/Trap/ITrapState.h"
#include <SFML/System/Clock.hpp>

class ExplodingState : public ITrapState 
{
public:
    ExplodingState(sf::Time animationDuration);
    void onEnter(TrapPlant& plant) override;
    std::unique_ptr<ITrapState> update(TrapPlant& plant, const sf::Time&) override;
    void handleCollision(TrapPlant&, Zombie&) override {};

private:
    sf::Clock m_animationClock;
    sf::Time m_animationDuration;
};