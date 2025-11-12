#pragma once
#include "Strategy/Shoot/IShootStrategy.h"
#include <string>

class BidirectionalShootStrategy : public IShootStrategy {
public:
    explicit BidirectionalShootStrategy(std::string bulletId);
    void beginShootSequence(const sf::Vector2f& position, const sf::Vector2f& direction) override;
    BulletVector update(const sf::Time& dt) override;
    bool isFinished() const override;

private:
    std::string m_bulletId;
    bool m_hasFired;
    sf::Vector2f m_direction;
};