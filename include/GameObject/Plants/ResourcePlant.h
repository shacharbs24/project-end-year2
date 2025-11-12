#pragma once
#include "Plant.h"

class GameObjectManager;
class PlayerResourceManager;

class ResourcePlant : public Plant {
public:
	ResourcePlant(const CreationParams& p, const PlantData::ResourcePlantDef& def);
	void update(const sf::Time& dt) override;

private:
	sf::Clock m_productionClock;
	sf::Time m_productionCooldown;

	GameObjectManager& m_objManager;
	PlayerResourceManager& m_PlayerResourceManager;

	int m_amount;
};