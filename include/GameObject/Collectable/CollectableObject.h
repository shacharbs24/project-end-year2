#pragma once

#include "GameObject/GameObject.h"

class CollectableObject : public GameObject
{
public:
	using GameObject::GameObject;

	~CollectableObject() = default;

	virtual void handleMouseClick(const sf::Vector2f& mousePos);
	virtual void handleEvent(const sf::Event& event) override;
	virtual void update(const sf::Time&) override {}

	virtual bool isDone() const { return m_isCollected; }
	virtual bool isCollidable() const override { return false; }

protected:
	virtual void collect();
	bool m_isCollected = false;
};