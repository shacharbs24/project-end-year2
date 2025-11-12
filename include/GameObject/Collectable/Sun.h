#pragma once
#include "GameObject/Collectable/CollectableObject.h"
#include <SFML/System/Clock.hpp>
#include "Config/SunData.h"
#include "Animation/Animation.h"

class PlayerResourceManager;
class IMovementStrategy;
class ILifetimeStrategy;

class Sun : public CollectableObject {
public:
	Sun(const CreationParams& p, const SunData::Definition& def,
		std::unique_ptr<IMovementStrategy> moveStrategy,
		std::unique_ptr<ILifetimeStrategy> lifetimeStrategy);

	void update(const sf::Time& dt) override;
	bool isDone() const;

private:
	void collect();

	int m_value;
	float m_speed;

	std::unique_ptr<IMovementStrategy> m_movementStrategy;
	std::unique_ptr<ILifetimeStrategy> m_lifetimeStrategy;
	PlayerResourceManager& m_PlayerResourceManager;

	Animation m_animation;
};