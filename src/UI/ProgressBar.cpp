#include "UI/ProgressBar.h"
#include "Managers/TextureManager.h"
#include <algorithm>
#include <iostream>

ProgressBar::ProgressBar()
{
	auto& tex = TextureManager::getInstance().getTexture("other_plants");

	m_bg.setTexture(tex);
	m_head.setTexture(tex);
	m_flagProto.setTexture(tex);
	m_bg.setTextureRect({ 138, 180, 260, 25 });
	m_head.setTextureRect({ 399, 179, 26, 27 });
	m_flagProto.setTextureRect({ 426, 182, 24, 24 });
	m_fill.setFillColor(sf::Color(57, 255, 20));
	m_fill.setSize({ 0.f, 9.f });
}

void ProgressBar::setPosition(const sf::Vector2f& pos)
{
	m_bg.setPosition(pos);
	m_fill.setPosition(pos.x + m_bg.getTextureRect().width - 4, pos.y + 6.f);
	m_head.setPosition(pos.x + m_bg.getTextureRect().width - 4 - m_head.getGlobalBounds().width * 0.5f, pos.y + 6.f);
}

void ProgressBar::update(float progress, const std::vector<float>& flagPos)
{
	progress = std::clamp(progress, 0.f, 1.f);

	const float border = m_bg.getPosition().x + m_bg.getTextureRect().width - 4.f - (m_bg.getTextureRect().width - 8.f) * progress;

	m_fill.setSize({ (m_bg.getTextureRect().width - 8.f) * progress, m_fill.getSize().y });
	m_fill.setPosition(border - 5, m_bg.getPosition().y + 6.f);
	m_head.setPosition(border - m_head.getGlobalBounds().width * 0.5f, m_bg.getPosition().y);

	if (m_flags.size() != flagPos.size())
		m_flags.assign(flagPos.size(), m_flagProto);

	for (size_t i = 0; i < flagPos.size(); ++i)
	{
		float x = m_bg.getPosition().x + m_bg.getTextureRect().width - 4.f
			- (m_bg.getTextureRect().width - 8.f) * flagPos[i] - m_flagProto.getGlobalBounds().width / 2.f;

		m_flags[i].setPosition(x, m_bg.getPosition().y);
	}
}

void ProgressBar::draw(sf::RenderWindow& w) const
{
	w.draw(m_bg);
	w.draw(m_fill);
	for (const auto& f : m_flags) w.draw(f);
	w.draw(m_head);
}