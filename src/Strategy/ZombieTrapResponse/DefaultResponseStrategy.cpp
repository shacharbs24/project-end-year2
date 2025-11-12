#include "Strategy/ZombieTrapResponse/DefaultResponseStrategy.h"
#include "GameObject/Zombies/Zombie.h"
#include "GameObject/Plants/TrapPlant.h"

DefaultResponseStrategy::DefaultResponseStrategy()
	: m_damageInterval(sf::seconds(1.5f))
{
}

void DefaultResponseStrategy::onCollisionWith(Zombie& owner, TrapPlant& plant)
{
	if (m_damageClock.getElapsedTime() >= m_damageInterval)
	{
		constexpr int ZOMBIE_DAMAGE_PER_SECOND = 10;
		constexpr int PLANT_DAMAGE_PER_SECOND = ZOMBIE_DAMAGE_PER_SECOND / 2 + 10;
		owner.takeDamage(ZOMBIE_DAMAGE_PER_SECOND);
		plant.takeDamage(PLANT_DAMAGE_PER_SECOND);
		m_damageClock.restart();
	}
}