#pragma once
#include <memory>
#include <SFML/System/Time.hpp>

class TrapPlant;
class Zombie;

class ITrapState {
public:
    virtual ~ITrapState() = default;

    virtual std::unique_ptr<ITrapState> update(TrapPlant& plant, const sf::Time& dt) = 0;

    virtual void handleCollision(TrapPlant& plant, Zombie& zombie) = 0;

    virtual void onEnter(TrapPlant&) {}
    virtual void onExit(TrapPlant&) {}
};