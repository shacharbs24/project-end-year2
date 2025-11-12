#include "Config/ZombieData.h"

namespace ZombieID
{
	const std::string regularZombie = "regular_zombie";
	const std::string bucketheadZombie = "buckethead_zombie";
	const std::string coneheadZombie = "conehead_zombie";
	const std::string flagZombie = "flag_zombie";
	const std::string zomboni = "zomboni";
	const std::string peashooterZombie = "peashooter_zombie";
	const std::string gatlingPeaZombie = "gatling_pea_zombie";
}

namespace Sheets
{
	const std::string regularZombie = "regular_zombie";
	const std::string bucketheadZombie = "regular_zombie";
	const std::string coneHeadZombie = "regular_zombie";
	const std::string flagZombie = "regular_zombie";
	const std::string zomboni = "regular_zombie";
	const std::string peashooterZombie = "shooting_zombie";
	const std::string gatlingPeaZombie = "shooting_zombie";
}

namespace FirstSprite
{
	const SpriteDef regularZombie{ {0, 0, 42, 54}, {23.5f, 0.f} };
	const SpriteDef bucketheadZombie{ {0, 110, 44, 52}, {22.f, 0.f} };
	const SpriteDef coneheadZombie{ {0, 221, 44, 57}, {22.f, 0.f} };
	const SpriteDef flagZombie{ {0, 336, 47, 54}, {22.f, 0.f} };
	const SpriteDef zomboni{ {1, 444, 59, 64}, {30.f, 5.f} };
	const SpriteDef peashooterZombie{ {0, 0, 39, 41}, {20.f, -13.f} };
	const SpriteDef gatlingPeaZombie{ {0, 125, 44, 47}, {20.f, -5.f} };
	const SpriteDef regularZombieEat{ { 0, 54, 37, 51}, {0.f, 0.f} };
	const SpriteDef bucketheadZombieEat{ { 0, 168, 37, 51}, {0.f, 0.f} };
	const SpriteDef coneheadZombieEat{ { 0, 278, 37, 56}, {0.f, 0.f} };
	const SpriteDef flagZombieEat{ { 0, 390, 43, 54}, {0.f, 0.f} };
	const SpriteDef peashooterZombieEat{ { 0, 41, 33, 41}, {0.f, 0.f} };
	const SpriteDef gatlingPeaZombieEat{ { 0, 173, 40, 47}, {0.f, 0.f} };
}

namespace ZombieData {
	const Definition regularZombie = {
		ZombieID::regularZombie, Sheets::regularZombie, FirstSprite::regularZombie, 100, 25.f, 10, 7, 7,
		 FirstSprite::regularZombieEat, 8.f, 7.f
	};

	const Definition bucketheadZombie = {
		ZombieID::bucketheadZombie, Sheets::bucketheadZombie, FirstSprite::bucketheadZombie, 200, 25.f, 10,7, 7,
		FirstSprite::bucketheadZombieEat, 8.f, 7.f
	};

	const Definition coneheadZombie = {
		ZombieID::coneheadZombie, Sheets::coneHeadZombie, FirstSprite::coneheadZombie, 150, 25.f, 10,7,7,
		FirstSprite::coneheadZombieEat, 8.f, 7.f
	};

	const Definition flagZombie = {
		ZombieID::flagZombie, Sheets::flagZombie, FirstSprite::flagZombie, 100, 25.f, 10,7,7,
		FirstSprite::flagZombieEat, 8.f, 7.f
	};

	const Definition zomboni = {
		ZombieID::zomboni, Sheets::zomboni, FirstSprite::zomboni, 300, 30.f, 1000,10, 10, FirstSprite::zomboni,
		10.f, 10.f
	};

	const ShootingZombieDef peashooterZombie = {
		{ ZombieID::peashooterZombie, Sheets::peashooterZombie, FirstSprite::peashooterZombie, 100, 20.f, 10 ,7 ,7,
		FirstSprite::peashooterZombieEat, 11.f, 9.f}, sf::seconds(1.5f)
	};

	const ShootingZombieDef gatlingPeaZombie = {
		{ ZombieID::gatlingPeaZombie, Sheets::gatlingPeaZombie, FirstSprite::gatlingPeaZombie, 150, 20.f, 10 ,7,7,
		FirstSprite::gatlingPeaZombieEat,12.f, 11.f}, sf::seconds(7.f)
	};
}