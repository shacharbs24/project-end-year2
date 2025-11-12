#include "Config/SunData.h"

namespace Sheets
{
	const std::string sun = "resource_plant";
}

namespace FirstSprite
{
	const SpriteDef sun{ {0, 79, 26, 26}, {5.f, 5.f} };
}

namespace SunData
{
	const Definition fallingSun = { "falling_sun", Sheets::sun, FirstSprite::sun, 25, 50.f, 2 };
	const Definition stationarySun = { "stationary_sun", Sheets::sun, FirstSprite::sun, 25, 0.f, 2 };
}