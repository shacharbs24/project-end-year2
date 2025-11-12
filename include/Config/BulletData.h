#pragma once
#include <SFML/System/Vector2.hpp>
#include <string>
#include "SpriteDef.h"

namespace BulletID
{
	extern const std::string regularBullet;
	extern const std::string slowingBullet;
	extern const std::string plantBullet;
	extern const std::string zombieBullet;
}

namespace spriteSize
{
	inline const sf::Vector2f bulletScale = { 3.f,3.f };
}

namespace Sheets
{
	extern const std::string regularBullet;
	extern const std::string SlowingBullet;
}

namespace FirstSprite
{
	extern const SpriteDef regularBullet;
	extern const SpriteDef SlowingBullet;
}

namespace BulletData {
	struct Definition {
		std::string id;
		std::string sheet;
		FirstSprite::SpriteDef spriteDef;
		int damage;
		float speed;
		int frameCount;
		float offset = 1.f;
	};

	extern const Definition regularBullet;
	extern const Definition SlowingBullet;
	extern const Definition zombieBullet;
}
