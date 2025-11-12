#pragma once
#include "Plant.h"

class ITrapBehaviorStrategy;
class ITrapState;
class Zombie;

class TrapPlant : public Plant {
public:
	TrapPlant(const CreationParams& p, const PlantData::Definition& def, std::unique_ptr< ITrapBehaviorStrategy> coll,
		std::unique_ptr< ITrapState> state);
	void update(const sf::Time& dt) override;

	void handleCollision(Zombie& zombie);
	void triggerBehavior(Zombie& zombie);

	void move(sf::Vector2f offset) { m_sprite.move(offset); }

	void setAnimation(Animation* anim) { m_currentAnimation = anim; }
	Animation* getSpawningAnimation() { return &m_spawningAnimation; }
	Animation* getReadyAnimation() { return &m_readyAnimation; }
	Animation* getExplosionAnimation() { return &m_explosionAnimation; }

	void setSpriteRect(const sf::IntRect& rect) { m_sprite.setTextureRect(rect); }
	void changeState(std::unique_ptr<ITrapState> newState);

private:
	std::unique_ptr<ITrapBehaviorStrategy> m_behaviorStrategy;
	std::unique_ptr<ITrapState> m_currentState;

	Animation m_spawningAnimation;
	Animation m_readyAnimation;
	Animation m_explosionAnimation;
};