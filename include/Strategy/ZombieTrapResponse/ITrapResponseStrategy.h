#pragma once

class Zombie;
class TrapPlant;

class ITrapResponseStrategy {
public:
    virtual ~ITrapResponseStrategy() = default;
    virtual void onCollisionWith(Zombie& owner, TrapPlant& trap) = 0;
};