#pragma once
#include <memory>
#include <SFML/System/Time.hpp>
class Plant;
class Zombie;

class IEffectStrategy {
public:
	virtual ~IEffectStrategy() = default;

	virtual void apply(Plant& target) const = 0;
	virtual void apply(Zombie& target) const = 0;
	virtual void update(const sf::Time&) {}
	virtual void applyDamageBoost(float, sf::Time) {}
};




