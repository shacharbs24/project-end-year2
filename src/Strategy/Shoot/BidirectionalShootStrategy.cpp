#include "Strategy/Shoot/BidirectionalShootStrategy.h"
#include "Factory/Factory.h"
#include "Factory/CreationParams.h"
#include "GameObject/GameObject.h"

BidirectionalShootStrategy::BidirectionalShootStrategy(std::string bulletId)
    : m_bulletId(std::move(bulletId)), m_hasFired(true) {}

void BidirectionalShootStrategy::beginShootSequence(const sf::Vector2f& position, const sf::Vector2f& direction)
{
    m_position = position;
    m_hasFired = false;
    m_direction = direction;
}

IShootStrategy::BulletVector BidirectionalShootStrategy::update(const sf::Time&)
{
    BulletVector newBullets;
    if (m_hasFired) return newBullets;

    CreationParams paramsForward = { .position = m_position, .direction = m_direction };
    auto forBullet = Factory::create(m_bulletId, paramsForward);
    newBullets.push_back(std::move(forBullet));
    

    CreationParams paramsBackward = { .position = m_position, .direction = -m_direction };
    auto backBullet = Factory::create(m_bulletId, paramsBackward);
    backBullet->rotate(180.f);
    newBullets.push_back(std::move(backBullet));
   
    m_hasFired = true;
    return newBullets;
}

bool BidirectionalShootStrategy::isFinished() const
{
    return m_hasFired;
}