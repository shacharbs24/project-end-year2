#pragma once
#include <SFML/System/Vector2.hpp>
#include <string>
#include "SpriteDef.h"
#include <SFML/System/Time.hpp>

namespace spriteSize {
	inline const sf::Vector2f ZombieScale = { 3.f,3.f };
}

#define ZOMBIES_NAMES_LIST(ACTION, TYPE) \
    ACTION(TYPE, regularZombie) \
    ACTION(TYPE, bucketheadZombie) \
    ACTION(TYPE, coneheadZombie) \
    ACTION(TYPE, flagZombie) \
    ACTION(TYPE, zomboni) \
    ACTION(TYPE, peashooterZombie) \
    ACTION(TYPE, gatlingPeaZombie)

#define DECLARE_EXTERN(type,name) extern const type name;

namespace ZombieID
{
	ZOMBIES_NAMES_LIST(DECLARE_EXTERN, std::string)
}

namespace Sheets
{
	ZOMBIES_NAMES_LIST(DECLARE_EXTERN, std::string)
}

namespace FirstSprite
{
	ZOMBIES_NAMES_LIST(DECLARE_EXTERN, SpriteDef)
	extern const SpriteDef regularZombieEat;
	extern const SpriteDef bucketheadZombieEat;
	extern const SpriteDef coneheadZombieEat;
	extern const SpriteDef flagZombieEat;
	extern const SpriteDef peashooterZombieEat;
	extern const SpriteDef gatlingPeaZombieEat;
}

namespace ZombieData 
{
	struct Definition {
		std::string id;
		std::string sheet;
		FirstSprite::SpriteDef spriteDef;
		int health;
		float speed;
		int damage;
		int walkFrameCount;
		int eatFrameCount;
		FirstSprite::SpriteDef eatSpriteDef;
		float offset = 8.f;
		float eatOffset = 8.f;
	};
	struct ShootingZombieDef : public Definition { sf::Time cooldown; };

	extern const Definition regularZombie;
	extern const Definition bucketheadZombie;
	extern const Definition coneheadZombie;
	extern const Definition flagZombie;
	extern const Definition zomboni;
	extern const ShootingZombieDef peashooterZombie;
	extern const ShootingZombieDef gatlingPeaZombie;
}

#undef DECLARE_EXTERN
#undef ZOMBIES_NAMES_LIST
