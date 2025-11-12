#include "Strategy/Targeting/BidirectionalTargetingStrategy.h"
#include "Managers/TargetingSystem.h"

bool BidirectionalTargetingStrategy::shouldShoot(const Plant& plant, const TargetingSystem& system) const 
{
    return system.hasZombieInFront(plant) || system.hasZombieBehind(plant);
}