#include "ShootingLogicHandler.h"
#include "States/Controller/GameState.h"
#include "GameObject/GameObject.h"

void ShootingLogicHandler::handleShootingUpdate(const sf::Time& dt, const sf::Sprite& sprite, sf::Vector2f shootDirection, sf::Vector2f bulletOffset)
{
	if (m_isShooting)
	{
		auto newBullets = m_shootStrategy->update(dt);
		for (auto& bullet : newBullets)
		{
			m_gameObjectManager->addObject(std::move(bullet));
		}

		if (m_shootStrategy->isFinished())
			m_isShooting = false;
	}
	else
	{
		bool cooldownFinished = (m_shootClock.getElapsedTime() >= m_shootCooldown * m_cooldownMultipler);

		if (!m_hasFiredOnce)
			cooldownFinished = true;

		if (cooldownFinished) {
			m_shootClock.restart();
			m_isShooting = true;
			m_hasFiredOnce = true;

			auto pos = sprite.getPosition();
			sf::Vector2f bulletPos = pos + bulletOffset;
			m_shootStrategy->beginShootSequence(bulletPos, shootDirection);
		}
	}
}