#pragma once
#include "States/Trap/ITrapState.h"
#include <SFML/System/Clock.hpp>

class ArmingState : public ITrapState {
public:
    ArmingState(sf::Time armingTime);
    std::unique_ptr<ITrapState> update(TrapPlant& plant, const sf::Time& dt) override;
    void handleCollision(TrapPlant& plant, Zombie& zombie) override;
    void onEnter(TrapPlant& plant) override;
private:
    sf::Clock m_armingClock;
    sf::Time m_armingTime;
};