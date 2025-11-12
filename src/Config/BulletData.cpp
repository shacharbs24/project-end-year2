#include "Config/BulletData.h"

namespace BulletID
{
	const std::string regularBullet = "regular_bullet";
	const std::string slowingBullet = "slowing_bullet";
	const std::string plantBullet = "plant_bullet";
	const std::string zombieBullet = "zombie_bullet";
}

namespace Sheets
{
	const std::string regularBullet = "shooting_plant";
	const std::string SlowingBullet = "shooting_plant";
}

namespace FirstSprite
{
	const SpriteDef regularBullet{ {112, 43, 14, 15}, {5.f, 0.f} };
	const SpriteDef SlowingBullet{ {161, 36, 21, 23}, {5.f, 10.f} };
}

namespace BulletData
{
	const Definition regularBullet = {
		BulletID::regularBullet, Sheets::regularBullet, FirstSprite::regularBullet, 20, 400.f, 3
	};

	const Definition SlowingBullet = {
		BulletID::slowingBullet, Sheets::SlowingBullet, FirstSprite::SlowingBullet, 10, 400.f, 4, 2
	};

	const Definition zombieBullet = {
		BulletID::zombieBullet, Sheets::regularBullet, FirstSprite::regularBullet, 10, 400.f, 3
	};
}