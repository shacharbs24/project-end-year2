#include "Strategy/Shoot/BurstFireStrategy.h"
#include "Factory/Factory.h"
#include "Factory/CreationParams.h"
#include "GameObject/Bullets/Bullet.h"

BurstFireStrategy::BurstFireStrategy(const std::string& bulletId, int numShots, sf::Time delayBetweenShots)
    : m_bulletId(bulletId), m_totalShots(numShots), m_delay(delayBetweenShots) {}


void BurstFireStrategy::beginShootSequence(const sf::Vector2f& position, const sf::Vector2f& direction)
{
    m_shotsFired = 0;
    m_position = position;
    m_direction = direction;
    m_clock.restart();
}

IShootStrategy::BulletVector BurstFireStrategy::update(const sf::Time&) 
{
    BulletVector newBullets;
    if (isFinished()) return newBullets;

    if (m_clock.getElapsedTime() >= m_delay) 
    {
        m_clock.restart();
        m_shotsFired++;
        CreationParams params = { .position = m_position, .direction = m_direction };
        auto obj = Factory::create(m_bulletId, params);
        newBullets.push_back(std::move(obj));
    }
    return newBullets;
}

bool BurstFireStrategy::isFinished() const
{
    return m_shotsFired >= m_totalShots;
}