#include "GameObject/Zombies/ShootingZombie.h"
#include "States/Controller/GameState.h"
#include "Strategy/Shoot/SingleShotStrategy.h"
#include "Strategy/Shoot/BurstFireStrategy.h"
#include "Strategy/Movement/LinearMovementStrategy.h"
#include "Managers/TargetingSystem.h"
#include <Strategy/ZombieTrapResponse/DefaultResponseStrategy.h>
#include <Config/BulletData.h>

namespace {
	auto move = []() { return std::make_unique<LinearMovementStrategy>(); };
	bool ok =
		GameObject::registerType<ShootingZombie>(ZombieData::peashooterZombie, move,
			[] { return std::make_unique<SingleShotStrategy>(BulletID::zombieBullet); }) &&
		GameObject::registerType<ShootingZombie>(ZombieData::gatlingPeaZombie, move,
			[] { return std::make_unique<BurstFireStrategy>(BulletID::zombieBullet, 5, sf::seconds(0.3f)); });
}

ShootingZombie::ShootingZombie(const CreationParams& p, const ZombieData::ShootingZombieDef& def,
	std::unique_ptr<IMovementStrategy> moveStrategy,
	std::unique_ptr<IShootStrategy> shootStrategy)
	: Zombie(def, p, std::move(moveStrategy), std::make_unique<DefaultResponseStrategy>())
{
	m_shootStrategy = std::move(shootStrategy);
	m_shootCooldown = def.cooldown;
	setObjectManager(p.objectManager);
}

void ShootingZombie::attemptShooting(const sf::Time& dt)
{
	if (m_targetingSystem.hasPlantInFront(*this))
		handleShootingUpdate(dt, m_sprite, { -1.f,0.f }, { -30.f,35.f });
}