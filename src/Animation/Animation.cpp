#include "Animation/Animation.h"
#include <cmath>

void Animation::setup(const sf::IntRect& baseRect, int frameCount, float switchTime, float offset, bool loop)
{
	m_baseRect = baseRect;
	m_frameCount = frameCount;
	m_switchTime = switchTime;
	m_totalTime = 0.0f;
	m_currentFrame = 0;
	uvRect = m_baseRect;
	m_offset = offset;
	m_loop = loop;
	m_stride = std::abs(m_baseRect.width) + int(m_offset);
	uvRect.top = m_baseRect.top;
	uvRect.height = m_baseRect.height;
	uvRect.width = std::abs(m_baseRect.width);
	uvRect.left = m_baseRect.left;
}

void Animation::update(float deltaTime)
{
    if (m_frameCount <= 1) return;

    m_totalTime += deltaTime;

    if (m_totalTime >= m_switchTime)
    {
        m_totalTime -= m_switchTime;
        ++m_currentFrame;
		m_currentFrame = (!m_loop && m_currentFrame >= m_frameCount) ?	m_frameCount - 1 : m_currentFrame % m_frameCount;
    }
	uvRect.left = m_baseRect.left + m_currentFrame * m_stride;
}

bool Animation::isDone() const
{
    return !m_loop && m_currentFrame >= m_frameCount - 1;
}