#pragma once
#include <SFML/System/Time.hpp>
#include <memory>

class Zombie;
class Plant;

class IZombieState {
public:
	virtual ~IZombieState() = default;

	virtual void onEnter(Zombie& zombie) = 0;

	virtual std::unique_ptr<IZombieState> update(Zombie&, const sf::Time&) { return nullptr; }
	virtual std::unique_ptr<IZombieState> onCollision(Zombie&, Plant*) { return nullptr; }

	virtual void onExit(Zombie& zombie) = 0;
};