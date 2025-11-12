#include "GameObject/GameObject.h"
#include "Board.h"

GameObject::GameObject(sf::Vector2f position, const sf::Texture& tex, const FirstSprite::SpriteDef& recs)
{
	m_sprite.setTexture(tex);
	m_sprite.setTextureRect(recs.rect);
	m_sprite.setOrigin(recs.origin);
	m_sprite.setPosition(position);
	m_sprite.setScale(recs.scale);
	m_gridRow = Board::pixelToGrid(getCenter()).y;
}

void GameObject::draw(sf::RenderWindow& w) const
{
	w.draw(m_sprite);
}

sf::Vector2f GameObject::getCenter() const
{
	if (!m_centerCached)
	{
		sf::FloatRect bounds = m_sprite.getGlobalBounds();

		m_cachedCenter = sf::Vector2f(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
		m_centerCached = true;
	}
	return m_cachedCenter;
}

void GameObject::updateAnimation(const sf::Time& dt)
{
	if (m_currentAnimation)
	{
		m_currentAnimation->update(dt.asSeconds());
		m_sprite.setTextureRect(m_currentAnimation->uvRect);
	}
}
