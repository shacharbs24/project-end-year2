#pragma once
#include "ILifetimeStrategy.h"
#include <SFML/System/Clock.hpp>

class TimerLifetimeStrategy : public ILifetimeStrategy {
public:
    explicit TimerLifetimeStrategy(sf::Time lifetime) : m_lifetime(lifetime) { m_clock.restart();}
    void update(const sf::Time&, const sf::Sprite&) override {}
    bool isDone() const override {return m_clock.getElapsedTime() >= m_lifetime;}

private:
    sf::Clock m_clock;
    sf::Time m_lifetime;
};