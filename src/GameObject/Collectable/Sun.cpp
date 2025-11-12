#include "GameObject/Collectable/Sun.h"
#include "States/Controller/GameState.h"
#include "Managers/TextureManager.h"
#include <Strategy/LifeTime/OffScreenLifetimeStrategy.h>
#include <Strategy/Movement/StationaryMovementStrategy.h>
#include <Strategy/LifeTime/TimerLifetimeStrategy.h>
#include <Strategy/Movement/LinearMovementStrategy.h>
#include "Managers/PlayerResourceManager.h"
#include "Managers/AudioManager.h"

namespace {
	bool ok = GameObject::registerType<Sun>(SunData::fallingSun,
		[] { return std::make_unique<LinearMovementStrategy>(); },
		[] { return std::make_unique<OffScreenLifetimeStrategy>(); }) &&
		GameObject::registerType<Sun>(SunData::stationarySun,
			[] { return std::make_unique<StationaryMovementStrategy>(); },
			[] { return std::make_unique<TimerLifetimeStrategy>(sf::seconds(6.f)); }
		);
}

Sun::Sun(const CreationParams& p, const SunData::Definition& def,
	std::unique_ptr<IMovementStrategy> moveStrategy,
	std::unique_ptr<ILifetimeStrategy> lifetimeStrategy)
	: CollectableObject(p.position, TextureManager::getInstance().getTexture(def.sheet), FirstSprite::sun),
	m_value(def.value), m_movementStrategy(std::move(moveStrategy)),
	m_lifetimeStrategy(std::move(lifetimeStrategy)), m_speed(def.speed), m_PlayerResourceManager(*p.PlayerResourceManager)
{
	m_animation.setup(def.spriteDef.rect, def.frameCount, 0.4f, def.offset);
	m_currentAnimation = &m_animation;
}

void Sun::update(const sf::Time& dt)
{
	updateAnimation(dt);

	if (m_movementStrategy->move(m_sprite, dt, m_speed, { 0.f, 1.f }))
		invalidateCache();

	if (m_lifetimeStrategy)
	{
		m_lifetimeStrategy->update(dt, m_sprite);
		if (m_lifetimeStrategy->isDone())
			setToDelete(true);
	}
}

void Sun::collect()
{
	if (!isDone())
	{
		m_PlayerResourceManager.addSun(m_value);
		AudioManager::getInstance().playFx("Sun");
		CollectableObject::collect();
	}
}

bool Sun::isDone() const
{
	return CollectableObject::isDone() || (m_lifetimeStrategy && m_lifetimeStrategy->isDone());
}