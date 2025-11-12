#pragma once
#include <SFML/Graphics.hpp>
#include "Managers/TextureManager.h"

sf::Text createText(unsigned size, sf::Color fill, sf::Color out, float thick, const sf::Font& font = TextureManager::getInstance().getFont("font"));
sf::IntRect calculateSpriteRect(int index);

bool levelScriptExists(int levelNumber);
void centerOrigin(sf::Text& t);
