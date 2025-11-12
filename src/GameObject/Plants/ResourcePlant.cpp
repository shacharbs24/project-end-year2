#include "GameObject/Plants/ResourcePlant.h"
#include "GameObject/Collectable/Sun.h"
#include "Managers/GameObjectManager.h"

namespace
{
	bool ok = 
		GameObject::registerType<ResourcePlant>(PlantData::sunFlower) &&
		GameObject::registerType<ResourcePlant>(PlantData::doubleSunFlower);
}

ResourcePlant::ResourcePlant(const CreationParams& p, const PlantData::ResourcePlantDef& def)
	: Plant(def, p), m_productionCooldown(def.actionCooldown), m_amount(def.sunProductionAmount),
	m_objManager(*p.objectManager), m_PlayerResourceManager(*p.PlayerResourceManager)
{}

void ResourcePlant::update(const sf::Time& dt)
{
	Plant::update(dt);
	if (m_productionClock.getElapsedTime() >= m_productionCooldown)
	{
		m_productionClock.restart();
		sf::Vector2f sunPos = m_sprite.getPosition() + sf::Vector2f(20.f, -20.f);
		CreationParams params = { .position = sunPos, .PlayerResourceManager = &m_PlayerResourceManager };
		static constexpr float xOffset = -50.f;
		static constexpr float yOffset = 30.f;

		for (int i = 0; i < m_amount; ++i)
		{
			auto sunObject = Factory::create("stationary_sun", params);
			m_objManager.addObject(std::move(sunObject));
			params.position += {xOffset, yOffset};
		}
	}
}