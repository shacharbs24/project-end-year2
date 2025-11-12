#pragma once
#include "Strategy/Effects/IEffectStrategy.h"
#include "SFML/System/Clock.hpp"

class DamageEffect : public IEffectStrategy {
public:
	explicit DamageEffect(int damage);
	void apply(Zombie& target) const override;
	void apply(Plant& target) const override;

	void update(const sf::Time& dt) override;
	void applyDamageBoost(float multiplier, sf::Time duration) override;

	static void startGlobalBoost(float mul, sf::Time dur);

private:
	int m_damage;
	float m_multiplier = 1.0f;
	sf::Clock m_timer;
	sf::Time m_duration;
};