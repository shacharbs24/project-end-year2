#include "GameObject/Plants/TrapPlant.h"  
#include "Strategy/Trap/PassiveStrategy.h"  
#include "Strategy/Trap/ExplodeStrategy.h"  
#include <States/Trap/ReadyState.h>
#include <States/Trap/ArmingState.h>

namespace {
	bool ok =  
		GameObject::registerType<TrapPlant>(PlantData::spikeWeed, 
			[]() { return std::make_unique<PassiveStrategy>(); },
			[]() {return std::make_unique<ReadyState>(); }) &&
		GameObject::registerType<TrapPlant>(PlantData::potatoMine,
  			[]() { return std::make_unique<ExplodeStrategy>(); },
	        []() {return std::make_unique<ArmingState>(sf::seconds(15.f)); });
}

TrapPlant::TrapPlant(const CreationParams& p, const PlantData::Definition& def, std::unique_ptr< ITrapBehaviorStrategy> coll,
	std::unique_ptr< ITrapState> state)
	: Plant(def, p ), m_behaviorStrategy(std::move(coll)), m_currentState(std::move(state))
{
	m_spawningAnimation.setup({ 1, 35, 30, 22 }, 3, 0.2f, 1.f, false);
	m_explosionAnimation.setup({ 1, 86, 78, 60 }, 8, 0.15f, 1.f, false); 
	m_readyAnimation.setup(def.spriteDef.rect, def.frameCount, 0.3f, def.offset);
	m_currentState->onEnter(*this);
}


void TrapPlant::update(const sf::Time& dt)
{
	if (m_currentState)
	{
		auto newState = m_currentState->update(*this, dt);
		if (newState) 
			changeState(std::move(newState));
	}

	Plant::update(dt);
}


void TrapPlant::handleCollision(Zombie& zombie)
{
	if (m_currentState)
		m_currentState->handleCollision(*this, zombie);
}

void TrapPlant::changeState(std::unique_ptr<ITrapState> newState)
{
	if (m_currentState)
		m_currentState->onExit(*this);

	m_currentState = std::move(newState);

	if (m_currentState)
		m_currentState->onEnter(*this);

	if (!m_observers.empty())
		notifyObservers();
}

void TrapPlant::triggerBehavior(Zombie& zombie)
{
	if (m_behaviorStrategy)
		m_behaviorStrategy->onCollision(*this, zombie);
}