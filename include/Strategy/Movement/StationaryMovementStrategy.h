#pragma once
#include "IMovementStrategy.h"

class StationaryMovementStrategy : public IMovementStrategy {
public:
	bool move(sf::Sprite&, const sf::Time&, float, sf::Vector2f) override { return false; }
};