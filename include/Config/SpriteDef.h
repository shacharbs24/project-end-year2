#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace FirstSprite 
{
    struct SpriteDef 
    {
        sf::IntRect rect;
        sf::Vector2f origin;
        sf::Vector2f scale = { 3.f,3.f };
    };
}