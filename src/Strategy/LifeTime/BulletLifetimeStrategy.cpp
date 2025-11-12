#include "Strategy/LifeTime/BulletLifetimeStrategy.h"
#include <Config/GameConfig.h>

void BulletLifetimeStrategy::update(const sf::Time&, const sf::Sprite& sprite)
{
    sf::Vector2f pos = sprite.getPosition();
    sf::FloatRect bounds = sprite.getGlobalBounds();
    m_isDone = (pos.x < -1.f || pos.x > window::width + 1.f || pos.y < -1.f || pos.y > window::height + 1.f);
}
