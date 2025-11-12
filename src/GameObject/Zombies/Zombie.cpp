#include "GameObject/Zombies/Zombie.h"
#include "GameObject/Plants/Plant.h"
#include <States/Zombie/WalkingState.h>
#include "Managers/LevelLogicManager.h"
#include "Managers/TargetingSystem.h"
#include "UI/UIManager.h"
#include <Strategy/Movement/LinearMovementStrategy.h>
#include "Managers/AudioManager.h"
#include <States/Zombie/FrozenState.h>
#include <Config/GameConfig.h>
#include "Strategy/ZombieTrapResponse/ITrapResponseStrategy.h"

Zombie::Zombie(const ZombieData::Definition& def, const CreationParams& params,
	std::unique_ptr<IMovementStrategy> moveStrategy, std::unique_ptr<ITrapResponseStrategy> trapResponseStrategy)
	: GameObject(params.position, TextureManager::getInstance().getTexture(def.sheet), def.spriteDef)
	, m_health(def.health)
	, m_speed(def.speed)
	, m_originalSpeed(def.speed)
	, m_dmg(def.damage)
	, m_movementStrategy(std::move(moveStrategy))
	, m_currentState(std::make_unique<WalkingState>())
	, m_trapResponseStrategy(std::move(trapResponseStrategy)),
	m_targetingSystem(*params.TargetingSystem),
	m_levelLogicManager(*params.levelLogicManager)
{
	m_walkAnimation.setup(def.spriteDef.rect, def.walkFrameCount, 0.3f, def.offset);
	m_eatAnimation.setup(def.eatSpriteDef.rect, def.eatFrameCount, 0.3f, def.offset);
	m_currentAnimation = &m_walkAnimation;
	m_currentState->onEnter(*this);
}

Zombie::~Zombie()
{
	if (m_eatingTarget)
		m_eatingTarget->removeObserver(this);
}

void Zombie::update(const sf::Time& dt)
{
	handleSlowing();

	if (m_currentState)
	{
		auto newState = m_currentState->update(*this, dt);
		if (newState) changeState(std::move(newState));
	}

	updateAnimation(dt);

	const auto posX = m_sprite.getPosition().x;
	if (!m_hasBeenCounted)
	{
		if (posX < window::width)
		{
			AudioManager::getInstance().playFx("Groan");
			m_targetingSystem.addZombie(*this);
			m_hasBeenCounted = true;
		}
	}

	if (posX < gridSize::startPos.x - 50.f)
	{
		m_levelLogicManager.setGameOver(true);
		setToDelete(true);
	}
}

void Zombie::takeDamage(int damage)
{
	m_health -= damage;
	if (m_health <= 0 && !m_alreadyDead)
	{
		m_alreadyDead = true;
		m_targetingSystem.removeZombie(*this);
		m_levelLogicManager.onZombieDefeated(getCenter());
		setToDelete(true);
	}
}

void Zombie::changeState(std::unique_ptr<IZombieState> newState)
{
	if (m_currentState)
		m_currentState->onExit(*this);

	m_currentState = std::move(newState);

	if (m_currentState)
		m_currentState->onEnter(*this);
}

void Zombie::onCollisionWithPlant(Plant* plant)
{
	auto newState = m_currentState->onCollision(*this, plant);
	if (newState) 
		changeState(std::move(newState));
	
}

void Zombie::onCollisionWithTrap(TrapPlant& trap)
{
	if (m_trapResponseStrategy)
		m_trapResponseStrategy->onCollisionWith(*this, trap);
}

void Zombie::move(const sf::Time dt)
{
	if (m_movementStrategy->move(m_sprite, dt, m_speed, { -1.f, 0.f }))
		invalidateCache();
}

void Zombie::onNotify(const GameObject& subject)
{
	if (m_eatingTarget == &subject) 
	{
		setEatingTarget(nullptr);
		changeState(std::make_unique<WalkingState>());
	}
}

void Zombie::applySlowingEffect(float factor, sf::Time duration)
{
	if (!m_isSlowed)
	{
		m_speed *= factor;
		m_isSlowed = true;
	}
	m_slowDuration = duration;
	m_slowClock.restart();
}

void Zombie::handleSlowing()
{
	if (m_isSlowed && m_slowClock.getElapsedTime() >= m_slowDuration)
	{
		m_speed = m_originalSpeed;
		setColor(sf::Color::White);
		m_isSlowed = false;
	}
}

void Zombie::applyFreezeEffect(sf::Time duration)
{
	changeState(std::make_unique<FrozenState>(std::move(m_currentState), duration));
}