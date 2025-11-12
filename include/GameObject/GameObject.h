#pragma once
#include <SFML/Graphics.hpp>
#include "Factory/Factory.h"
#include "Factory/CreationParams.h"
#include <Config/SpriteDef.h>
#include "Animation/Animation.h"

class GameState;

class GameObject {
public:
	GameObject(sf::Vector2f position, const sf::Texture& tex, const FirstSprite::SpriteDef& recs);
	virtual ~GameObject() = default;
	virtual void draw(sf::RenderWindow& w) const;
	virtual void update(const sf::Time&) = 0;
	virtual void handleEvent(const sf::Event&) {}

	virtual bool isToDelete() const { return m_toDelete; }
	virtual void setToDelete(bool toDelete) { m_toDelete = toDelete; }

	virtual void takeDamage(int) {}
	virtual int getHealth() const { return 0; }

	virtual void applySlowingEffect(float, sf::Time) {}
	virtual void applyFreezeEffect(sf::Time) {};

	sf::Vector2f getCenter() const;
	sf::FloatRect getGlobalBounds() const { return m_sprite.getGlobalBounds(); }

	void rotate(float r) { m_sprite.rotate(r); }
	int getGridRow() const { return m_gridRow; }

	template<typename T, typename Def, typename... FactoryFns>
	static bool registerType(const Def& def, FactoryFns&&... fns);

	virtual void applyFireRateBoost(float, sf::Time) {}
	virtual void applyDamageBoost(float, sf::Time) {}
	virtual bool isCollidable() const { return true; }

protected:
	sf::Sprite m_sprite;
	bool m_toDelete = false;
	int m_gridRow;
	Animation* m_currentAnimation = nullptr;

	void invalidateCache() { m_centerCached = false; }
	void updateAnimation(const sf::Time& dt);

private:
	mutable sf::Vector2f m_cachedCenter;
	mutable bool m_centerCached = false;
};

template<typename T, typename Def, typename... FactoryFns>
bool GameObject::registerType(const Def& def, FactoryFns&&... fns)
{
	return Factory::registerit(
		def.id,
		[def, ...fns = std::forward<FactoryFns>(fns)]
		(const CreationParams& params)
		{
			return std::make_unique<T>(params, def, fns()...);
		});
}