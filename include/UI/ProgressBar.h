#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class ProgressBar
{
public:

	ProgressBar();
	void setPosition(const sf::Vector2f& pos);
	void update(float progress, const std::vector<float>& flagPositions = {});
	void draw(sf::RenderWindow& w) const;

private:

	sf::Sprite m_bg;
	sf::RectangleShape m_fill;
	sf::Sprite m_head;
	sf::Sprite m_flagProto;
	std::vector<sf::Sprite> m_flags;
};
