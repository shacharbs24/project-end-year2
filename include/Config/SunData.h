#pragma once
#include <string>
#include "SpriteDef.h"

namespace Sheets
{
	extern const std::string sun;
}

namespace FirstSprite
{
	extern const SpriteDef sun;
}

namespace SunData
{
	struct Definition
	{
		std::string id;
		std::string sheet;
		FirstSprite::SpriteDef spriteDef;
		int value;
		float speed;
		int frameCount;
		float offset = 1.f;
	};

	extern const Definition fallingSun;
	extern const Definition stationarySun;
}
