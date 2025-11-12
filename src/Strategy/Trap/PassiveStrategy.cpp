#include "Strategy/Trap/PassiveStrategy.h"
#include "GameObject/Zombies/Zombie.h"
#include "GameObject/Plants/TrapPlant.h"


void PassiveStrategy::onCollision(TrapPlant& self, Zombie& triggeringZombie)
{
    triggeringZombie.onCollisionWithTrap(self);
}