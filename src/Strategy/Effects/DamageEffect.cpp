#include "Strategy/Effects/DamageEffect.h"
#include "GameObject/Zombies/Zombie.h"
#include "GameObject/Plants/Plant.h"
#include <iostream>

namespace
{
	float g_boostMul = 1.f;
	sf::Clock g_boostClk;
	sf::Time g_boostDur = sf::Time::Zero;
	bool boostActive() { return g_boostMul > 1.f && g_boostClk.getElapsedTime() < g_boostDur; }
}

DamageEffect::DamageEffect(int damage) : m_damage(damage)
{
	if (boostActive())
		applyDamageBoost(g_boostMul, g_boostDur - g_boostClk.getElapsedTime());
}

void DamageEffect::startGlobalBoost(float mul, sf::Time dur)
{
	g_boostMul = mul;
	g_boostDur = dur;
	g_boostClk.restart();
}

void DamageEffect::apply(Zombie& target) const
{
	target.takeDamage(int(m_damage * m_multiplier));
}

void DamageEffect::apply(Plant& target) const
{
	target.takeDamage(m_damage);
}

void DamageEffect::update(const sf::Time&)
{
	if (m_timer.getElapsedTime() >= m_duration)
		m_multiplier = 1.0f;
}

void DamageEffect::applyDamageBoost(float multiplier, sf::Time duration)
{
	m_multiplier = multiplier;
	m_duration = duration;
	m_timer.restart();
}