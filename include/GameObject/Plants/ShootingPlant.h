#pragma once
#include "Plant.h"
#include "ShootingLogicHandler.h"

class GameState;
class IShootStrategy;
class ITargetingStrategy;

class ShootingPlant : public Plant, public ShootingLogicHandler {
public:
	ShootingPlant(const CreationParams& p, const PlantData::Definition& def,
		std::unique_ptr<IShootStrategy> shoot,
		std::unique_ptr<ITargetingStrategy> targetStrategy);
	void update(const sf::Time& dt) override;
	void applyFireRateBoost(float multiplier, sf::Time duration) override;

private:
	std::unique_ptr<ITargetingStrategy> m_targetingStrategy;
	sf::Clock m_fireRateEffectClock;
	sf::Time m_fireRateEffectDuration = sf::Time::Zero;
};