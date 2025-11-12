#pragma once
#include "IZombieState.h"
#include <SFML/System/Clock.hpp>


class FrozenState : public IZombieState {
public:
    FrozenState(std::unique_ptr<IZombieState> previousState, sf::Time duration);
    std::unique_ptr<IZombieState> update(Zombie&, const sf::Time&) override;
    void onEnter(Zombie& zombie) override;
    void onExit(Zombie& zombie) override;

private:
    std::unique_ptr<IZombieState> m_prevState;
    sf::Time m_duration;
    sf::Clock m_timer;
};