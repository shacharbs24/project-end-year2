#pragma once
#include "SpriteDef.h"
#include <string>

#define GIFT_NAMES_LIST(ACTION, TYPE) \
    ACTION(TYPE, freezeGift) \
    ACTION(TYPE, sunGift) \
    ACTION(TYPE, dmgGift) \
    ACTION(TYPE, fireRateGift)

#define DECLARE_EXTERN(type,name) extern const type name;

namespace GiftID
{
	GIFT_NAMES_LIST(DECLARE_EXTERN, std::string)
}

namespace FirstSprite
{
	GIFT_NAMES_LIST(DECLARE_EXTERN, SpriteDef)
}

namespace GiftData
{
	struct Definition
	{
		std::string id;
		FirstSprite::SpriteDef spriteDef;
		std::string sheet = "gifts";
	};
	GIFT_NAMES_LIST(DECLARE_EXTERN, Definition)
}

#undef DECLARE_EXTERN
#undef PLANT_NAMES_LIST
