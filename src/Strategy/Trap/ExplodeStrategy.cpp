#include "Strategy/Trap/ExplodeStrategy.h"
#include "GameObject/Plants/TrapPlant.h"
#include "GameObject/Zombies/Zombie.h"
#include "States/Controller/GameState.h" 
#include "Managers/AudioManager.h"
#include <States/Trap/ExplodingState.h>

void ExplodeStrategy::onCollision(TrapPlant& self, Zombie& triggeringZombie)
{
    triggeringZombie.takeDamage(2000);
    AudioManager::getInstance().playFx("explosion");
    self.changeState(std::make_unique<ExplodingState>(sf::seconds(0.6f)));
}