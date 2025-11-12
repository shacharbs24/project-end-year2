#include "Utiles.h"
#include <filesystem>

sf::Text createText(unsigned size, sf::Color fill, sf::Color out, float thick, const sf::Font& font)
{
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(size);
	text.setFillColor(fill);
	text.setOutlineColor(out);
	text.setOutlineThickness(thick);
	return text;
}

sf::IntRect calculateSpriteRect(int index)
{
	const int START_X = 2;
	const int START_Y = 2;
	const int SPRITE_WIDTH = 100;
	const int SPRITE_HEIGHT = 100;
	const int GAP = 2;

	int left = START_X + index * (SPRITE_WIDTH + GAP);

	return sf::IntRect(left, START_Y, SPRITE_WIDTH, SPRITE_HEIGHT);
}

bool levelScriptExists(int levelNumber)
{
	namespace fs = std::filesystem;
	fs::path scriptPath = fs::path(("level_" + std::to_string(levelNumber) + ".txt"));

	return fs::exists(scriptPath);
}

void centerOrigin(sf::Text& t)
{
	const auto r = t.getLocalBounds();
	t.setOrigin(r.left + r.width / 2.f, r.top + r.height / 2.f);
}