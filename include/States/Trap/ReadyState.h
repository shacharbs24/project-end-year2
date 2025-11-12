#pragma once
#include "States/Trap/ITrapState.h"

class ReadyState : public ITrapState {
public:
    std::unique_ptr<ITrapState> update(TrapPlant& plant, const sf::Time& dt) override;
    void handleCollision(TrapPlant& plant, Zombie& zombie) override;
    void onEnter(TrapPlant& plant) override;
};