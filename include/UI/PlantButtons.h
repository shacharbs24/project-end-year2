#pragma once
#include <vector>
#include <string>
#include "Button/Button.h"
#include "PlantButtonData.h"
#include <unordered_map>
#include <functional>
#include <Command/SelectPlantCommand.h>

class GameState;
class PlayerResourceManager;
class UIManager;

class PlantButtons {
public:
	struct Raw { std::string id; int cost; sf::Time cooldown; sf::IntRect sheetRect; sf::IntRect barRect; std::string textureKey; };

	PlantButtons(PlayerResourceManager& PlayerResourceManager, UIManager& ui);
	void handleEvent(const sf::Event& e);
	void draw(sf::RenderWindow& win) const;
	void update(const sf::Time& dt);

	void startPlantCooldown(const std::string& plantId);

	static std::unordered_map<std::string, int> createCostMap();

	std::function<std::unique_ptr<SelectPlantCommand>(const Raw&)> onSelectPlant;

private:
	static const std::vector<Raw> createData();
	static const std::vector<PlantButtons::Raw>& getRawData();

	std::vector<PlantButtonData> m_buttons;
	std::unordered_map<std::string, PlantButtonData*> m_buttonMap;

	const sf::Texture& m_sheet;
	PlayerResourceManager& m_playerResourceManager;
	UIManager& m_ui;

	sf::Clock m_clock;
	PlantButtonData makePlant(const PlantButtons::Raw& raw, const sf::Texture& sheet, float posX, float posY);
};