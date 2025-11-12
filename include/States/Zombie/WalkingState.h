#pragma once
#include "IZombieState.h"


class WalkingState : public IZombieState {
public:
    void onEnter(Zombie& zombie) override;
    std::unique_ptr<IZombieState> update(Zombie& zombie, const sf::Time& dt) override;
    std::unique_ptr<IZombieState> onCollision(Zombie& zombie, Plant* plant)  override;
    void onExit(Zombie&) override {};
};