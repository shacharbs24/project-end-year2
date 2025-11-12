#include "Board.h"
#include "Config/GameConfig.h"
#include "Managers/TextureManager.h"
#include "Factory/Factory.h"
#include "States/Controller/GameState.h"
#include "Managers/PlayerResourceManager.h"
#include "UI/UIManager.h"
#include "GameObject/GameObject.h"

Board::Board(UIManager& ui, PlayerResourceManager& rm) : m_grid{ false }, m_ui(ui), m_playerResourceManager(rm)
{}

void Board::placePlant(int r, int c, const std::string& plantId)
{
	if (m_playerResourceManager.buyPlant(plantId))
	{
		m_ui.startPlantCooldown(plantId);
		onAddPlant(gridToPixel(r, c), plantId);
		m_grid[r][c] = true;
		m_ui.cancelSelection();
	}
}

void Board::handleEvent(const sf::Event& event) {
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2i pos = pixelToGrid({ float(event.mouseButton.x), float(event.mouseButton.y) });

		if (pos.y >= 0 && pos.y < ROWS && pos.x >= 0 && pos.x < COLS && m_ui.isPlantSelected() && isEmpty(pos.y, pos.x))
		{
			placePlant(pos.y, pos.x, m_ui.getSelectedItem());
			m_ui.cancelSelection();
		}
	}
}

sf::Vector2f Board::gridToPixel(int r, int c)
{
	float topLeftX = gridSize::startPos.x + c * gridSize::floorSize.x;
	float topLeftY = gridSize::startPos.y + r * gridSize::floorSize.y;
	return { topLeftX + gridSize::floorSize.x / 2.0f, topLeftY + gridSize::floorSize.y / 2.0f };
}

sf::Vector2i Board::pixelToGrid(const sf::Vector2f& pixel)
{
	float relativeX = pixel.x - gridSize::startPos.x;
	float relativeY = pixel.y - gridSize::startPos.y;
	int c = int(relativeX / gridSize::floorSize.x);
	int r = int(relativeY / gridSize::floorSize.y);
	return { c, r };
}

void Board::clearCellAtPixel(const sf::Vector2f& pos)
{
	auto gridPos = pixelToGrid(pos);
	if (gridPos.x >= 0 && gridPos.x < COLS && gridPos.y >= 0 && gridPos.y < ROWS)
		m_grid[gridPos.y][gridPos.x] = false;
}