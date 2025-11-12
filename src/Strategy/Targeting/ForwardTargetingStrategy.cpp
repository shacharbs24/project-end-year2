#include "Strategy/Targeting/ForwardTargetingStrategy.h"
#include "Managers/TargetingSystem.h"

bool ForwardTargetingStrategy::shouldShoot(const Plant& plant, const TargetingSystem& system) const 
{
    return system.hasZombieInFront(plant);
}