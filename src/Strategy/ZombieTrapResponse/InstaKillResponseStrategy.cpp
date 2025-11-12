#include "Strategy/ZombieTrapResponse/InstaKillResponseStrategy.h"
#include "GameObject/Zombies/Zombie.h"
#include "GameObject/Plants/TrapPlant.h" 

void InstaKillResponseStrategy::onCollisionWith(Zombie& owner, TrapPlant& trap)
{
    owner.takeDamage(owner.getHealth() + 1);
    trap.die();
}