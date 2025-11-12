#pragma once
#include <string>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include "SpriteDef.h"
#include <SFML/System/Time.hpp>

namespace spriteSize {
	inline const sf::Vector2f plantScale = { 3.f,3.f };
}

#define PLANT_NAMES_LIST(ACTION, TYPE) \
    ACTION(TYPE, doubleSunFlower) \
    ACTION(TYPE, gatlingPea) \
    ACTION(TYPE, snowPea) \
    ACTION(TYPE, peashooter) \
    ACTION(TYPE, potatoMine) \
    ACTION(TYPE, repeater) \
    ACTION(TYPE, spikeWeed) \
    ACTION(TYPE, sunflower) \
    ACTION(TYPE, wallPotato) \
    ACTION(TYPE, tallNut) \
    ACTION(TYPE, splitPea)

#define DECLARE_EXTERN(type,name) extern const type name;

namespace PlantID
{
	PLANT_NAMES_LIST(DECLARE_EXTERN, std::string)
		extern const std::string shovel;
}

namespace Sheets
{
	PLANT_NAMES_LIST(DECLARE_EXTERN, std::string)
		extern const std::string shovel;
}

namespace FirstSprite
{
	PLANT_NAMES_LIST(DECLARE_EXTERN, SpriteDef)
		extern const SpriteDef shovel;
}

namespace PlantData
{
	struct Definition
	{
		const std::string id;
		std::string sheet;
		FirstSprite::SpriteDef spriteDef;
		sf::Time actionCooldown;
		int health;
		int frameCount;
		float offset = 1.f;
	};

	struct ResourcePlantDef : public Definition { int sunProductionAmount; };

	extern const Definition peashooter;
	extern const Definition snowPea;
	extern const Definition repeater;
	extern const Definition gatlingPea;
	extern const ResourcePlantDef sunFlower;
	extern const ResourcePlantDef doubleSunFlower;
	extern const Definition potatoMine;
	extern const Definition spikeWeed;
	extern const Definition wallPotato;
	extern const Definition tallNut;
	extern const Definition splitPea;
}

#undef DECLARE_EXTERN
#undef PLANT_NAMES_LIST
