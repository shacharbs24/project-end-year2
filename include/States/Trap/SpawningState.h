#pragma once
#include "States/Trap/ITrapState.h"
#include <SFML/System/Clock.hpp>

class SpawningState : public ITrapState
{
public:
    SpawningState(const sf::Time& duration = sf::seconds(0.6f));
    std::unique_ptr<ITrapState> update(TrapPlant&, const sf::Time&) override;
    void handleCollision(TrapPlant&, Zombie&) override {};
    void onEnter(TrapPlant& plant) override;

private:
    sf::Clock m_animationClock;
    sf::Time m_animationDuration;
};