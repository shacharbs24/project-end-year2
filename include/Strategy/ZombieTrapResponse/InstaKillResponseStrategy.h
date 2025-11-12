#pragma once
#include "Strategy/ZombieTrapResponse/ITrapResponseStrategy.h"

class InstaKillResponseStrategy : public ITrapResponseStrategy {
public:

    void onCollisionWith(Zombie& owner, TrapPlant& trap) override;
};