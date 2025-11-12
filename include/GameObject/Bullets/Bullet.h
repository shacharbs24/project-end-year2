#pragma once
#include "GameObject/GameObject.h"
#include "Strategy/Movement/IMovementStrategy.h"
#include "Strategy/Effects/IEffectStrategy.h"
#include "Managers/TextureManager.h"
#include "Strategy/LifeTime/ILifetimeStrategy.h"
#include "Managers/AudioManager.h"
#include "Config/BulletData.h"
#include <Animation/Animation.h>

class Plant;
class Zombie;

template <typename TargetType>
class Bullet : public GameObject
{
public:
	Bullet(
		const CreationParams& p,
		const BulletData::Definition& def,
		std::unique_ptr<IMovementStrategy> moveStrategy,
		std::unique_ptr<ILifetimeStrategy> lifetimeStrategy,
		std::vector<std::unique_ptr<IEffectStrategy>> effects
	);

	void update(const sf::Time& dt) override;
	void onHit(TargetType& target);
	void applyDamageBoost(float multiplier, sf::Time duration) override;

private:
	sf::Vector2f m_direction;
	float m_speed;
	std::unique_ptr<IMovementStrategy> m_moveStrategy;
	std::unique_ptr<ILifetimeStrategy> m_lifetimeStrategy;
	std::vector<std::unique_ptr<IEffectStrategy>> m_effects;

	Animation m_hitAnimation;
	bool m_isHit = false;
};

template<typename TargetType>
Bullet<TargetType>::Bullet(const CreationParams& p, const BulletData::Definition& def,
	std::unique_ptr<IMovementStrategy> moveStrategy,
	std::unique_ptr<ILifetimeStrategy> lifetimeStrategy,
	std::vector<std::unique_ptr<IEffectStrategy>> effects)
	: GameObject(p.position, TextureManager::getInstance().getTexture(def.sheet), def.spriteDef),
	m_direction(*p.direction),
	m_speed(def.speed),
	m_moveStrategy(std::move(moveStrategy)),
	m_lifetimeStrategy(std::move(lifetimeStrategy)),
	m_effects(std::move(effects))
{
	m_hitAnimation.setup(def.spriteDef.rect, def.frameCount, 0.1f, def.offset, false);
}

template<typename TargetType>
void Bullet<TargetType>::update(const sf::Time& dt)
{
	if (m_isHit)
	{
		m_currentAnimation = &m_hitAnimation;
		updateAnimation(dt);
		if (m_currentAnimation->isDone())
			setToDelete(true);
		return;
	}

	if (m_speed > 0)
	{
		if (m_moveStrategy->move(m_sprite, dt, m_speed, m_direction))
			invalidateCache();
	}

	if (m_lifetimeStrategy)
	{
		m_lifetimeStrategy->update(dt, m_sprite);
		if (m_lifetimeStrategy->isDone())
			setToDelete(true);
	}
}

template<typename TargetType>
void Bullet<TargetType>::onHit(TargetType& target)
{
	if (m_isHit) return;
	for (const auto& effect : m_effects)
	{
		effect->apply(target);
	}
	m_isHit = true;
	m_speed = 0;
	AudioManager::getInstance().playFx("bullet");
}

template<typename TargetType>
void Bullet<TargetType>::applyDamageBoost(float multiplier, sf::Time duration)
{
	for (const auto& effect : m_effects)
	{
		effect->applyDamageBoost(multiplier, duration);
	}
}

using PlantBullet = Bullet<Zombie>;
using ZombieBullet = Bullet<Plant>;
