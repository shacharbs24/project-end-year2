#pragma once
#include "Strategy/Effects/IEffectStrategy.h"
#include <SFML/System/Time.hpp>

class SlowEffect : public IEffectStrategy {
public:
	SlowEffect(float factor, sf::Time duration);
	void apply(Plant&) const override {}
	void apply(Zombie& target) const override;

private:
	float m_factor;
	sf::Time m_duration;
};