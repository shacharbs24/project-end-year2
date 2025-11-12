#pragma once  
#include "Strategy/Trap/ITrapBehaviorStrategy.h"  

class PassiveStrategy : public ITrapBehaviorStrategy {
public:
    void onCollision(TrapPlant& self, Zombie& triggeringZombie) override;
};