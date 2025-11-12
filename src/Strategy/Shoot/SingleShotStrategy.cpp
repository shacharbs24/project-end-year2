#include "Strategy/Shoot/SingleShotStrategy.h"
#include "Factory/Factory.h"
#include "Factory/CreationParams.h"
#include "GameObject/Bullets/Bullet.h"

SingleShotStrategy::SingleShotStrategy(const std::string& bulletId)
	: m_bulletId(bulletId)
{}

void SingleShotStrategy::beginShootSequence(const sf::Vector2f& position, const sf::Vector2f& direction)
{
	m_hasFired = false;
	m_position = position;
	m_direction = direction;
}

IShootStrategy::BulletVector SingleShotStrategy::update(const sf::Time& )
{
    BulletVector newBullets;
    if (!m_hasFired)
    {
        CreationParams params = { .position = m_position, .direction = m_direction };
        auto obj = Factory::create(m_bulletId, params);
        newBullets.push_back(std::move(obj));
        m_hasFired = true;
    }
    return newBullets;
}

bool SingleShotStrategy::isFinished() const
{
	return m_hasFired;
}


