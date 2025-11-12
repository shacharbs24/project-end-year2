#pragma once
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "States/Controller/GameState.h"


class GameObject;

class IShootStrategy {
public:
	using BulletVector = std::vector<std::unique_ptr<GameObject>>;
    virtual ~IShootStrategy() = default;

    virtual void beginShootSequence(const sf::Vector2f& position, const sf::Vector2f& direction) = 0;
    virtual BulletVector update(const sf::Time& dt) = 0;
    virtual bool isFinished() const = 0;

protected:
    sf::Vector2f m_position;
    sf::Vector2f m_direction;
};