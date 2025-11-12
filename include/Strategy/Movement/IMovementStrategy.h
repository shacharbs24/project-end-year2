#pragma once
#include <SFML/Graphics.hpp>

class IMovementStrategy {
public:
	virtual ~IMovementStrategy() = default;

	virtual bool move(sf::Sprite& sprite, const sf::Time& dt, float speed, sf::Vector2f dir) = 0;
};