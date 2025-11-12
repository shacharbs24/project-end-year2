#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class SunCounter {
public:
	SunCounter();

	void update(int sunAmount);
	void draw(sf::RenderWindow& window) const;
	void setPosition(sf::Vector2f pos);

private:
	sf::Sprite m_background;
	sf::Sprite m_icon;
	sf::Text m_text;
};