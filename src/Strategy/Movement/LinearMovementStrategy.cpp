#include "Strategy/Movement/LinearMovementStrategy.h"

bool LinearMovementStrategy::move(sf::Sprite& sprite, const sf::Time& dt, float speed, sf::Vector2f dir)
{
	sf::Vector2f movement = dir * speed * dt.asSeconds();
	if (movement.x != 0.f || movement.y != 0.f)
	{
		sprite.move(movement);
		return true;
	}
	return false;
}