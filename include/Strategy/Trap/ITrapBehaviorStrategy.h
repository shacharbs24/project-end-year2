#pragma once

class TrapPlant;
class Zombie;

class ITrapBehaviorStrategy {
public:
    virtual ~ITrapBehaviorStrategy() = default;
    virtual void onCollision(TrapPlant& self, Zombie& triggeringZombie) = 0;
};