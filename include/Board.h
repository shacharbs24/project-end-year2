#pragma once
#include <array>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include <functional>

class UIManager;
class PlayerResourceManager;

class Board {
public:
	static constexpr int ROWS = 5;
	static constexpr int COLS = 9;
	using Grid = std::array<std::array<bool, COLS>, ROWS>;

	Board(UIManager& ui, PlayerResourceManager& rm);

	bool isEmpty(int r, int c) const { return !m_grid[r][c]; }
	void placePlant(int r, int c, const std::string& plant);

	void handleEvent(const sf::Event& e);

	void clearCellAtPixel(const sf::Vector2f& pos);
	static sf::Vector2i pixelToGrid(const sf::Vector2f& pixel);

	std::function<void(const sf::Vector2f&, const std::string&)> onAddPlant;

private:
	Grid m_grid;

	UIManager& m_ui;
	PlayerResourceManager& m_playerResourceManager;

	static sf::Vector2f gridToPixel(int r, int c);
};
