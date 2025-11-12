#pragma once
#include "Strategy/Shoot/IShootStrategy.h"
#include <string>
#include <SFML/System/Clock.hpp>

class BurstFireStrategy : public IShootStrategy {
public:
    BurstFireStrategy(const std::string& bulletId, int numShots, sf::Time delayBetweenShots);
    void beginShootSequence(const sf::Vector2f& position, const sf::Vector2f& direction) override;
    BulletVector update(const sf::Time& dt) override;
    bool isFinished() const override;
private:
    std::string m_bulletId;
    int m_totalShots;
    int m_shotsFired = 0;
    sf::Time m_delay;
    sf::Clock m_clock;

};