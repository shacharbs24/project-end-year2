#include "GameObject/Plants/ShootingPlant.h"
#include <GameObject/Bullets/Bullet.h>
#include <Strategy/Shoot/SingleShotStrategy.h>
#include <Strategy/Shoot/BurstFireStrategy.h>
#include <Strategy/Targeting/ForwardTargetingStrategy.h>
#include <Strategy/Targeting/BidirectionalTargetingStrategy.h>
#include <Strategy/Shoot/BidirectionalShootStrategy.h>
#include <Config/BulletData.h>

namespace {
	auto single = [](const std::string& id) {return [&id]() {return std::make_unique<SingleShotStrategy>(id); }; };
	auto burst = [](const std::string& id, int i, sf::Time t) {return [&id, i, t]() {return std::make_unique<BurstFireStrategy>(id, i, sf::seconds(0.3f)); }; };
	auto forward = []() {return std::make_unique<ForwardTargetingStrategy>(); };

	bool ok =
		GameObject::registerType<ShootingPlant>(PlantData::peashooter, single(BulletID::regularBullet), forward) &&
		GameObject::registerType<ShootingPlant>(PlantData::snowPea, single(BulletID::slowingBullet), forward) &&
		GameObject::registerType<ShootingPlant>(PlantData::repeater, burst(BulletID::regularBullet, 2, sf::seconds(0.3f)), forward) &&
		GameObject::registerType<ShootingPlant>(PlantData::gatlingPea, burst(BulletID::regularBullet, 5, sf::seconds(0.3f)), forward) &&
		GameObject::registerType<ShootingPlant>(PlantData::splitPea, [] {return std::make_unique<BidirectionalShootStrategy>(BulletID::regularBullet); }, [] {return std::make_unique<BidirectionalTargetingStrategy>(); });
}

ShootingPlant::ShootingPlant(const CreationParams& p, const PlantData::Definition& def,
	std::unique_ptr<IShootStrategy> shoot,
	std::unique_ptr<ITargetingStrategy> targetStrategy
)
	: Plant(def, p),
	m_targetingStrategy(std::move(targetStrategy))
{
	m_shootStrategy = std::move(shoot);
	m_shootCooldown = def.actionCooldown;
	setObjectManager(p.objectManager);
}

void ShootingPlant::update(const sf::Time& dt)
{
	Plant::update(dt);
	if (m_targetingStrategy->shouldShoot(*this, m_targetingSystem))
		handleShootingUpdate(dt, m_sprite, { 1.f, 0.f }, { 0.f, -35.f });

	if (m_fireRateEffectClock.getElapsedTime() > m_fireRateEffectDuration)
		m_cooldownMultipler = 1.f;
}

void ShootingPlant::applyFireRateBoost(float factor, sf::Time duration)
{
	m_cooldownMultipler = factor;
	m_fireRateEffectDuration = duration;
	m_fireRateEffectClock.restart();
}