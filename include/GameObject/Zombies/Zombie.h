#pragma once
#include "GameObject/GameObject.h"
#include <memory>
#include "Observer/IObserver.h"
#include "Animation/Animation.h"
#include "Config/ZombieData.h"

class Plant;
class TrapPlant;
class TargetingSystem;
class LevelLogicManager;
class IMovementStrategy;
class IZombieState;
class ITrapResponseStrategy;

class Zombie : public GameObject, public IObserver
{
public:
	Zombie(const ZombieData::Definition& def, const CreationParams& params,
		std::unique_ptr<IMovementStrategy> moveStrategy, std::unique_ptr<ITrapResponseStrategy> trapResponseStrategy);

	virtual ~Zombie() override;

	virtual void update(const sf::Time& dt);

	void takeDamage(int damage) override;
	void applySlowingEffect(float factor, sf::Time duration) override;
	void applyFreezeEffect(sf::Time duration) override;

	int getHealth() const override { return m_health;}
	int getDamage() const { return m_dmg; }

	void changeState(std::unique_ptr<IZombieState> newState);

	void onCollisionWithPlant(Plant* plant);
	void onCollisionWithTrap(TrapPlant& trap);

	void move(const sf::Time dt);
	virtual void attemptShooting(const sf::Time&) {};

	void setColor(const sf::Color& color) { m_sprite.setColor(color); }

	void setEatingTarget(Plant* target) { m_eatingTarget = target; }
	Plant* getEatingTarget() const { return m_eatingTarget; }

	void onNotify(const GameObject& subject) override;

	void setAnimation(Animation* animation) { m_currentAnimation = animation; }
	Animation* getEatAnimation() { return &m_eatAnimation; }
	Animation* getWalkAnimation() { return &m_walkAnimation; }

protected:
	int m_health;
	float m_speed;
	float m_originalSpeed;
	bool m_isSlowed = false;
	sf::Clock m_slowClock;
	sf::Time m_slowDuration;
	bool m_alreadyDead = false;
	int m_dmg;
	bool m_hasBeenCounted = false;

	std::unique_ptr<IZombieState> m_currentState;
	std::unique_ptr<IMovementStrategy> m_movementStrategy;
	std::unique_ptr<ITrapResponseStrategy> m_trapResponseStrategy;

	Plant* m_eatingTarget = nullptr;

	TargetingSystem& m_targetingSystem;
	LevelLogicManager& m_levelLogicManager;

	void handleSlowing();

	Animation m_walkAnimation;
	Animation m_eatAnimation;
};
