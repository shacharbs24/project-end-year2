#pragma once
#include "Strategy/ZombieTrapResponse/ITrapResponseStrategy.h"
#include <SFML/System/Clock.hpp>

class DefaultResponseStrategy : public ITrapResponseStrategy {
public:
    DefaultResponseStrategy();

    void onCollisionWith(Zombie& owner, TrapPlant&) override;
private:
    sf::Clock m_damageClock;
    sf::Time m_damageInterval;
};