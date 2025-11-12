#pragma once
#include <SFML/Graphics.hpp>

class ILifetimeStrategy {
public:
    virtual ~ILifetimeStrategy() = default;

    virtual void update(const sf::Time& dt, const sf::Sprite& sprite) = 0;

    virtual bool isDone() const = 0;
};