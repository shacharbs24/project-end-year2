#pragma once
#include "ILifetimeStrategy.h"
#include <SFML/Graphics/Sprite.hpp>

class BulletLifetimeStrategy : public ILifetimeStrategy {
public:
    void update(const sf::Time&, const sf::Sprite& sprite) override;
    bool isDone() const override { return m_isDone; }

private:
    bool m_isDone = false;
};