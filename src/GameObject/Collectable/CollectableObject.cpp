#include "GameObject/Collectable/CollectableObject.h"



void CollectableObject::handleMouseClick(const sf::Vector2f& mousePos)
{
	if (m_sprite.getGlobalBounds().contains(mousePos))
		collect();
}

void CollectableObject::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		handleMouseClick({ float(event.mouseButton.x),float(event.mouseButton.y) });
}

void CollectableObject::collect()
{
	m_isCollected = true;
	m_toDelete = true;
}

