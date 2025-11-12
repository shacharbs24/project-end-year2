#pragma once
#include "Strategy/Trap/ITrapBehaviorStrategy.h"

class ExplodeStrategy : public ITrapBehaviorStrategy {
public:
    void onCollision(TrapPlant& self, Zombie& triggeringZombie) override;
};