#include "States/Zombie/FrozenState.h"
#include "GameObject/Zombies/Zombie.h"
#include <Strategy/Effects/DamageEffect.h>

FrozenState::FrozenState(std::unique_ptr<IZombieState> previousState, sf::Time duration)
    : m_prevState(std::move(previousState)), m_duration(duration)
{}

std::unique_ptr<IZombieState> FrozenState::update(Zombie&, const sf::Time&)
{
	return m_timer.getElapsedTime() >= m_duration ? std::move(m_prevState) : nullptr;
}

void FrozenState::onEnter(Zombie& zombie)
{
    zombie.setAnimation(nullptr);
    zombie.setColor(sf::Color(100, 100, 255));
}

void FrozenState::onExit(Zombie& zombie)
{
    zombie.setColor(sf::Color::White);
}