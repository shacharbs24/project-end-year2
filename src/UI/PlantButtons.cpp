#include "UI/PlantButtons.h"
#include "Managers/TextureManager.h"
#include <Command/SelectPlantCommand.h>
#include "States/Controller/GameState.h"
#include <ranges>
#include <algorithm>
#include "Managers/PlayerResourceManager.h"
#include "UI/UIManager.h"
#include "Config/PlantData.h"

PlantButtonData PlantButtons::makePlant(const PlantButtons::Raw& raw,
	const sf::Texture& sheet, float posX, float posY)
{
	sf::Sprite spr;
	spr.setTexture(sheet);
	spr.setTextureRect(raw.barRect);
	spr.setScale({ 0.80f, 0.80f });
	spr.setPosition(posX, posY);

	auto cmd = std::make_unique<SelectPlantCommand>(m_ui, raw.id, raw.sheetRect, raw.textureKey);
	return PlantButtonData{ raw.id, raw.cost, raw.cooldown, std::move(spr), std::move(cmd) };
}

namespace {
	sf::IntRect calculateSpriteRect(int index)
	{
		constexpr int START_X = 2;
		constexpr int START_Y = 2;
		constexpr int SPRITE_WIDTH = 100;
		constexpr int SPRITE_HEIGHT = 100;
		constexpr int GAP = 2;

		int left = START_X + index * (SPRITE_WIDTH + GAP);

		return sf::IntRect(left, START_Y, SPRITE_WIDTH, SPRITE_HEIGHT);
	}
}

const std::vector<PlantButtons::Raw> PlantButtons::createData()
{
	std::vector<Raw> v = {
{ PlantID::wallPotato, 50, sf::seconds(10.f) ,FirstSprite::wallPotato.rect,calculateSpriteRect(0), Sheets::wallPotato},
{ PlantID::splitPea, 125, sf::seconds(7.f),FirstSprite::splitPea.rect,calculateSpriteRect(1), Sheets::splitPea},
{ PlantID::gatlingPea,250, sf::seconds(30.f) ,FirstSprite::gatlingPea.rect,calculateSpriteRect(2), Sheets::gatlingPea },
{PlantID::peashooter, 100, sf::seconds(7.f) , FirstSprite::peashooter.rect,calculateSpriteRect(3),Sheets::peashooter},
{PlantID::potatoMine, 25, sf::seconds(7.f),FirstSprite::potatoMine.rect,calculateSpriteRect(4), Sheets::potatoMine},
{PlantID::repeater, 200, sf::seconds(8.f),FirstSprite::repeater.rect,calculateSpriteRect(5), Sheets::repeater},
{PlantID::sunflower, 50, sf::seconds(5.f),FirstSprite::sunflower.rect,calculateSpriteRect(6), Sheets::sunflower},
{ PlantID::doubleSunFlower, 150, sf::seconds(15.f),FirstSprite::doubleSunFlower.rect,calculateSpriteRect(7), Sheets::doubleSunFlower},
{PlantID::snowPea, 175, sf::seconds(7.f), FirstSprite::snowPea.rect, calculateSpriteRect(8),Sheets::snowPea},
{PlantID::spikeWeed, 100,  sf::seconds(15.f) ,FirstSprite::spikeWeed.rect,calculateSpriteRect(9), Sheets::spikeWeed},
{PlantID::tallNut, 125, sf::seconds(20.f),FirstSprite::tallNut.rect,calculateSpriteRect(10), Sheets::tallNut}
	};

	std::ranges::sort(v, std::less<>{}, & PlantButtons::Raw::cost);
	return v;
}

PlantButtons::PlantButtons(PlayerResourceManager& PlayerResourceManager, UIManager& ui) :
	m_sheet(TextureManager::getInstance().getTexture("plants_bar")), m_playerResourceManager(PlayerResourceManager), m_ui(ui)
{
	constexpr float posX = 50.f;
	float posY = 0.f;

	const auto& rawDataVector = getRawData();

	m_buttons.reserve(rawDataVector.size());
	for (int i = 0; i < int(rawDataVector.size()); ++i)
	{
		const Raw& raw = rawDataVector[i];
		m_buttons.push_back(makePlant(raw, m_sheet, posX, posY));
		posY += 80;
	}

	for (auto& plantData : m_buttons)
	{
		m_buttonMap[plantData.id] = &plantData;
	}
}

void PlantButtons::handleEvent(const sf::Event& e) {
	if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.x < 150) 
	{
		for (auto& pd : m_buttons)
		{
			pd.handleClick(e, m_playerResourceManager.getSun());
		}
	}

	if (m_ui.isPlantSelected() && e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Right)
		m_ui.cancelSelection();
}

void PlantButtons::draw(sf::RenderWindow& w) const {
	for (auto& b : m_buttons)
		b.draw(w);
}

void PlantButtons::update(const sf::Time& dt)
{
	for (auto& p : m_buttons)
		p.update(dt, m_playerResourceManager.getSun());
}

void PlantButtons::startPlantCooldown(const std::string& plantId)
{
	if (m_buttonMap.contains(plantId))
		m_buttonMap.at(plantId)->startCooldown();

}

std::unordered_map<std::string, int> PlantButtons::createCostMap()
{
	std::unordered_map<std::string, int> costMap;

	for (const auto& rawData : getRawData())
	{
		costMap[rawData.id] = rawData.cost;
	}
	return costMap;
}

const std::vector<PlantButtons::Raw>& PlantButtons::getRawData()
{
	static const std::vector<Raw> s_rawData = createData();
	return s_rawData;
}