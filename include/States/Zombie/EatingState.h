#pragma once
#include "IZombieState.h"
#include <SFML/System/Clock.hpp>

class EatingState : public IZombieState {
public:
	void onEnter(Zombie& zombie) override;
	std::unique_ptr<IZombieState> update(Zombie& zombie, const sf::Time& dt) override;
	void onExit(Zombie& zombie) override;

private:
	sf::Clock m_eatingClock;
	sf::Time m_damageInterval = sf::seconds(1.0f);
};