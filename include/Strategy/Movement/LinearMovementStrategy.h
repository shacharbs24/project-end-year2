#pragma once
#include "IMovementStrategy.h"

class LinearMovementStrategy : public IMovementStrategy 
{
public:
	bool move(sf::Sprite& sprite, const sf::Time& dt, float speed, sf::Vector2f dir) override;
};