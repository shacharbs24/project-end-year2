#pragma once
#include "ILifetimeStrategy.h"
#include <SFML/Graphics/Sprite.hpp>
#include <Config/GameConfig.h>

class OffScreenLifetimeStrategy : public ILifetimeStrategy {
public:
	void update(const sf::Time&, const sf::Sprite& sprite) override{
		m_isDone = (sprite.getPosition().y > window::height + 50.f);
	}
	bool isDone() const override { return m_isDone; }

private:
	bool m_isDone = false;
};