#include "Strategy/Effects/SlowEffect.h"
#include "GameObject/Zombies/Zombie.h"
#include "GameObject/Plants/Plant.h"

SlowEffect::SlowEffect(float factor, sf::Time duration)
    : m_factor(factor), m_duration(duration) {}

void SlowEffect::apply(Zombie& target) const
{
    target.applySlowingEffect(m_factor, m_duration);
    target.setColor({ 135, 206, 250 });
}

