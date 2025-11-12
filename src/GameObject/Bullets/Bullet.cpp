#include "GameObject/Bullets/Bullet.h"
#include "Strategy/Movement/LinearMovementStrategy.h"
#include "Strategy/Effects/DamageEffect.h"
#include "Strategy/Effects/SlowEffect.h"
#include <Strategy/LifeTime/BulletLifetimeStrategy.h>

#include <vector>
#include <memory>

namespace
{
    auto regularE = []() {
        std::vector<std::unique_ptr<IEffectStrategy>> e;
        e.emplace_back(std::make_unique<DamageEffect>(20));
        return e;
        };
    auto slowingE = []() {
        std::vector<std::unique_ptr<IEffectStrategy>> e;
        e.emplace_back(std::make_unique<DamageEffect>(10));
        e.emplace_back(std::make_unique<SlowEffect>(0.5f, sf::seconds(5)));
        return e;
        };
    auto zombieE = []() {
        std::vector<std::unique_ptr<IEffectStrategy>> e;
        e.push_back(std::make_unique<DamageEffect>(20));
        return e;
        };

    auto linear = []() { return std::make_unique<LinearMovementStrategy>(); };
    auto lifetime = []() { return std::make_unique<BulletLifetimeStrategy>(); };

    const bool ok =
        GameObject::registerType<PlantBullet>(BulletData::regularBullet, linear, lifetime, regularE) &&
        GameObject::registerType<PlantBullet>(BulletData::SlowingBullet, linear, lifetime, slowingE) &&
        GameObject::registerType<ZombieBullet>(BulletData::zombieBullet, linear, lifetime, zombieE);
}