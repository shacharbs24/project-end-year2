#include "UI/SunCounter.h"
#include "Managers/TextureManager.h"
#include <Config/SunData.h>

SunCounter::SunCounter()
{
	m_background.setTexture(TextureManager::getInstance().getTexture("resource_plant"));
	m_background.setTextureRect({ 0, 106, 114, 51 });
	m_background.setScale(1.f, 1.f);

	m_icon.setTexture(TextureManager::getInstance().getTexture(Sheets::sun));
	m_icon.setTextureRect(FirstSprite::sun.rect);
	m_icon.setScale(1.5f, 1.5f);

	m_text.setFont(TextureManager::getInstance().getFont("font"));
	m_text.setCharacterSize(36);
	m_text.setFillColor(sf::Color(80, 50, 20));

	setPosition({ 200, 0.f });
}

void SunCounter::update(int sunAmount)
{
	m_text.setString(std::to_string(sunAmount));
}

void SunCounter::draw(sf::RenderWindow& window) const
{
	window.draw(m_background);
	window.draw(m_icon);
	window.draw(m_text);
}

void SunCounter::setPosition(sf::Vector2f pos)
{
	m_background.setPosition(pos);

	sf::FloatRect backgroundBounds = m_background.getGlobalBounds();

	float iconPaddingY = (backgroundBounds.height - m_icon.getGlobalBounds().height) / 2.f;
	m_icon.setPosition(pos.x + 1.f, pos.y + iconPaddingY);

	sf::FloatRect textBounds = m_text.getLocalBounds();
	float textPaddingY = (backgroundBounds.height - textBounds.height) / 2.f - 22.f;
	m_text.setPosition(m_icon.getPosition().x + m_icon.getGlobalBounds().width + 7.f,
		pos.y + textPaddingY);
}