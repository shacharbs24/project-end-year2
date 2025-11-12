#include "States/Zombie/EatingState.h"
#include "States/Zombie/WalkingState.h"
#include "GameObject/Zombies/Zombie.h"
#include "GameObject/Plants/Plant.h"
#include "Managers/AudioManager.h"

void EatingState::onEnter(Zombie& zombie) 
{
	m_eatingClock.restart();
	zombie.setAnimation(zombie.getEatAnimation());
}

std::unique_ptr<IZombieState> EatingState::update(Zombie& zombie, const sf::Time&) 
{
	auto target = zombie.getEatingTarget();

	if (target == nullptr)
		return std::make_unique<WalkingState>();

	if (m_eatingClock.getElapsedTime() >= m_damageInterval) 
	{
		target->takeDamage(zombie.getDamage());
		AudioManager::getInstance().playFx("eating");
		m_eatingClock.restart();
	}
	return nullptr;
}

void EatingState::onExit(Zombie& zombie) 
{
	if (auto* target = zombie.getEatingTarget()) 
		target->removeObserver(&zombie);
	zombie.setEatingTarget(nullptr);
}