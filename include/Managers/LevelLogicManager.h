#pragma once

#include <functional>
#include <memory>
#include <random>
#include <SFML/System/Time.hpp>
#include <string>
#include <States/Controller/GameOverState.h>
#include <States/Controller/WinState.h>

class SunSpawnerManager;
class UIManager;
class PlayerResourceManager;
class LevelScripter;

class LevelLogicManager
{
public:
	LevelLogicManager(UIManager& ui, PlayerResourceManager& rm, LevelScripter& scr, int level);
	~LevelLogicManager();

	void configure(const std::string& key, const std::string& value);
	void update(const sf::Time& dt);

	void setZombieCount(int count) { m_amountOfZombies = count; }
	void onZombieDefeated(const sf::Vector2f& position);

	void spawnZombie(const std::string& zombieType, const std::string& rowStr);

	float getProgress() const;
	const std::vector<float>& getFlagPositions() const;

	bool isGameOver() const { return m_isGameOver; }
	void setGameOver(bool isGameOver) { m_isGameOver = isGameOver; }
	bool getWin() const { return m_winGame; }
	int getLevel() const { return m_level; }

	std::function<void(const sf::Vector2f&, const std::string&)> onAddZombie;
	std::function<void(const sf::Vector2f&, const std::string&)> onAddSun;
	std::function<void(const sf::Vector2f&, const std::string&)> onAddGift;

private:
	void handleWinCondition() { m_winGame = true; }

	using ConfigAction = std::function<void(LevelLogicManager*, const std::string&)>;
	using ConfigActionMap = std::unordered_map<std::string, ConfigAction>;

	static ConfigActionMap createConfigActions();
	static const ConfigActionMap s_configActions;

	UIManager& m_ui;
	PlayerResourceManager& m_PlayerResourceManager;
	LevelScripter& m_levelScripter;
	std::unique_ptr <SunSpawnerManager> m_sunSpawner;

	int m_amountOfZombies;
	bool m_isGameOver = false;
	bool m_winGame = false;
	int m_level;

	std::mt19937 m_rng;
};