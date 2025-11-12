#include "Config/PlantData.h"


namespace PlantID
{
	const std::string doubleSunFlower = "double_sunflower";
	const std::string gatlingPea = "gatling_pea";
	const std::string snowPea = "snow_pea";
	const std::string peashooter = "peashooter";
	const std::string potatoMine = "potato_mine";
	const std::string repeater = "repeater";
	const std::string spikeWeed = "spike_weed";
	const std::string sunflower = "sunflower";
	const std::string wallPotato = "wall_potato";
	const std::string tallNut = "tall_nut";
	const std::string splitPea = "split_pea";
	const std::string shovel = "shovel";
}

namespace Sheets 
{
	const std::string doubleSunFlower = "resource_plant";
	const std::string gatlingPea = "shooting_plant";
	const std::string snowPea = "shooting_plant";
	const std::string peashooter = "shooting_plant";
	const std::string potatoMine = "other_plants";
	const std::string repeater = "shooting_plant";
	const std::string spikeWeed = "other_plants";
	const std::string sunflower = "resource_plant";
	const std::string wallPotato = "other_plants";
	const std::string tallNut = "other_plants";
	const std::string splitPea = "shooting_plant";
	const std::string shovel = "other_plants";
}

namespace FirstSprite
{
	const SpriteDef peashooter{ {2, 2, 28, 31}, {14.5f, 15.5f} };
	const SpriteDef snowPea{ {1, 68, 31, 32}, {17.f, 15.5f} };
	const SpriteDef doubleSunFlower{ {0, 35, 51, 43}, {30.f, 21.5f} };
	const SpriteDef gatlingPea{ {404, 2, 32, 35}, {18.f, 17.5f} };
	const SpriteDef potatoMine{ {1, 59, 29, 26}, {11.f, 11.f} };
	const SpriteDef repeater{ {1, 135, 29, 31}, {16.f, 15.5f} };
	const SpriteDef spikeWeed{ {1, 148, 33, 17}, {20.5f, -5.f} };
	const SpriteDef sunflower{ {2, 1, 28, 33}, {16.5f, 16.5f} };
	const SpriteDef wallPotato{ {1, 1, 28, 32}, {16.f, 16.f} };
	const SpriteDef tallNut{ {181,0,34,47}, {23.f,21.f} };
	const SpriteDef splitPea{ {194,133,36,35}, {25.f,16.f} };
	const SpriteDef shovel{ {1, 200, 32, 16}, {0.f, 0.f} };
}

namespace PlantData {
	const Definition peashooter = {
		PlantID::peashooter, Sheets::peashooter, FirstSprite::peashooter, sf::seconds(1.5f), 100, 8, 1.f
	};

	const Definition snowPea = {
		PlantID::snowPea, Sheets::snowPea, FirstSprite::snowPea, sf::seconds(2.f), 100, 8, 1.f
	};

	const Definition repeater{
		PlantID::repeater, Sheets::repeater, FirstSprite::repeater, sf::seconds(1.5f), 100, 5, 1.f
	};

	const Definition gatlingPea = {
		PlantID::gatlingPea, Sheets::gatlingPea, FirstSprite::gatlingPea, sf::seconds(10.f), 100, 7, 1.f
	};

	const ResourcePlantDef sunFlower{
		{ PlantID::sunflower, Sheets::sunflower, FirstSprite::sunflower, sf::seconds(7.f), 100,6 ,3.f }, 1
	};

	const ResourcePlantDef doubleSunFlower{
		{ PlantID::doubleSunFlower, Sheets::doubleSunFlower, FirstSprite::doubleSunFlower, sf::seconds(10.f), 100 , 10, 1.f}, 2
	};

	const Definition potatoMine{
		PlantID::potatoMine, Sheets::potatoMine, FirstSprite::potatoMine, sf::seconds(5.f), 100, 5, 1.f
	};

	const Definition spikeWeed{
		PlantID::spikeWeed, Sheets::spikeWeed, FirstSprite::spikeWeed, sf::seconds(0.f), 100, 7, 1.f
	};

	const Definition wallPotato{
		PlantID::wallPotato, Sheets::wallPotato, FirstSprite::wallPotato, sf::seconds(0.f), 200, 5, 1.f
	};

	const Definition tallNut{
		PlantID::tallNut, Sheets::tallNut, FirstSprite::tallNut, sf::seconds(0.f), 400, 9 ,1.f
	};

	const Definition splitPea{
	PlantID::splitPea, Sheets::splitPea, FirstSprite::splitPea, sf::seconds(5.f), 100,8, 1.f
	};
}