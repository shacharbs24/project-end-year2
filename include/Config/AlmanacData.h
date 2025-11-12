#pragma once
#include <array>
#include <SFML/Graphics/Rect.hpp>
#include "Config/PlantData.h"
#include "Config/ZombieData.h"
#include "Config/GiftData.h"
#include "Utiles.h"

namespace PlantAlmanac
{
	constexpr float cardSize = 150.f;
	constexpr float cardSpacing = 15.f;
	constexpr int cardsPerRow = 4;
	const sf::Vector2f startPos = { 30.f, 200.f };
	const sf::Vector2f selectedPlantPos = { 700.f, 195.f };
}

struct CardMeta {
	std::string id;
	sf::IntRect barRect;
	sf::IntRect infoRect;
};

static const std::vector<CardMeta> PLANT_CARDS{ {
	{ PlantID::wallPotato,       calculateSpriteRect(0),  { 2915, 0, 315, 471 } },
	{ PlantID::splitPea,         calculateSpriteRect(1),  { 1617, 0, 315, 471 } },
	{ PlantID::gatlingPea,       calculateSpriteRect(2),  { 323,  0, 315, 471 } },
	{ PlantID::peashooter,       calculateSpriteRect(3),  { 3239, 0, 316, 528 } },
	{ PlantID::potatoMine,       calculateSpriteRect(4),  { 970,  0, 315, 471 } },
	{ PlantID::repeater,         calculateSpriteRect(5),  { 646,  0, 315, 471 } },
	{ PlantID::sunflower,        calculateSpriteRect(6),  { 2265, 0, 315, 471 } },
	{ PlantID::doubleSunFlower,  calculateSpriteRect(7),  { 0,    0, 315, 471 } },
	{ PlantID::snowPea,          calculateSpriteRect(8),  { 1294, 0, 315, 471 } },
	{ PlantID::spikeWeed,        calculateSpriteRect(9),  { 1943, 0, 315, 471 } },
	{ PlantID::tallNut,          calculateSpriteRect(10), { 2590, 0, 315, 471 } }
} };

static const std::vector<CardMeta> ZOMBIE_CARDS{ {
	{ ZombieID::regularZombie,     calculateSpriteRect(0), { 1620, 0, 320, 490 } },
	{ ZombieID::bucketheadZombie,  calculateSpriteRect(1), { 0,    0, 320, 490 } },
	{ ZombieID::coneheadZombie,    calculateSpriteRect(2), { 320,  0, 320, 490 } },
	{ ZombieID::flagZombie,        calculateSpriteRect(3), { 650,  0, 320, 490 } },
	{ ZombieID::zomboni,           calculateSpriteRect(4), { 1945, 0, 320, 490 } },
	{ ZombieID::peashooterZombie,  calculateSpriteRect(5), { 1295, 0, 320, 490 } },
	{ ZombieID::gatlingPeaZombie,  calculateSpriteRect(6), { 975,  0, 320, 490 } }
} };

static const std::vector<CardMeta> GIFT_CARDS{ {
	{ GiftID::fireRateGift, calculateSpriteRect(0), {2, 2, 318, 483}},
	{ GiftID::sunGift,  calculateSpriteRect(1), { 322, 2, 318, 483 } },
	{ GiftID::dmgGift, calculateSpriteRect(2), { 970,  2, 318, 483  } },
	{ GiftID::freezeGift, calculateSpriteRect(3),  { 647,  2, 318, 483 } },
} };