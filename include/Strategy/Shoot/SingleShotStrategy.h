#pragma once
#include "Strategy/Shoot/IShootStrategy.h"
#include <string>
#include <SFML/System/Time.hpp>

class SingleShotStrategy : public IShootStrategy {
public:
    explicit SingleShotStrategy(const std::string& bulletId);
    void beginShootSequence(const sf::Vector2f& position, const sf::Vector2f& direction) override;
    BulletVector update(const sf::Time& dt) override;
    bool isFinished() const override;
private:
    std::string m_bulletId;
    BulletVector m_pendingBullets;
    bool m_hasFired;
};