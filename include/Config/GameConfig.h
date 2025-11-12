#pragma once
#include <SFML/System/Vector2.hpp>

namespace window {
	inline constexpr unsigned width = 1600;
	inline constexpr unsigned height = 900;
}

namespace gridSize {
	inline constexpr unsigned width = 1080;
	inline constexpr unsigned height = 720;
	const sf::Vector2f floorSize = { 120.f, 144.f };
	const sf::Vector2f startPos = { 370.f, 124.f };
}
