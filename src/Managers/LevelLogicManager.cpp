#include "Board.h"
#include "Config/GiftData.h"
#include "LevelManagment/LevelScripter.h"
#include "Logger.h"
#include "Managers/LevelLogicManager.h"
#include "Managers/PlayerResourceManager.h"
#include "Managers/SunSpawnerManager.h"
#include "UI/UIManager.h"
#include "Config/GameConfig.h"

LevelLogicManager::ConfigActionMap LevelLogicManager::createConfigActions()
{
	static ConfigActionMap actions;
	actions["level_type"] = [](LevelLogicManager* self, const std::string& val) {
		if (val == "day")
		{
			self->m_sunSpawner = std::make_unique<SunSpawnerManager>();
			self->m_sunSpawner->onAddObj = self->onAddSun;
			self->m_ui.setBackSprite("day_back");
		}
		else
		{
			self->m_ui.setBackSprite("night_back");
		}
		};

	actions["initial_sun"] = [](LevelLogicManager* self, const std::string& val) {
		self->m_PlayerResourceManager.addSun(std::stoi(val));
		};

	return actions;
}

const LevelLogicManager::ConfigActionMap LevelLogicManager::s_configActions = createConfigActions();

LevelLogicManager::LevelLogicManager(UIManager& ui, PlayerResourceManager& rm, LevelScripter& scr, int level) :
	m_ui(ui), m_PlayerResourceManager(rm), m_levelScripter(scr), m_level(level),
	m_rng(unsigned(time(nullptr)))
{
}

LevelLogicManager::~LevelLogicManager() = default;

void LevelLogicManager::configure(const std::string& key, const std::string& value)
{
	auto it = s_configActions.find(key);
	if (it != s_configActions.end())
	{
		try 
		{
			it->second(this, value);
		}
		catch (const std::exception& e)
		{
			Logger::getInstance().logError("Configuration Error for key '" + key + "' with value '" + value + "'. Details: " + e.what());
		}
	}
}

void LevelLogicManager::update(const sf::Time& dt)
{
	if (m_sunSpawner)
		m_sunSpawner->update(dt);

	if (m_amountOfZombies <= 0)
	{
		handleWinCondition();
		return;
	}
}

void LevelLogicManager::onZombieDefeated(const sf::Vector2f& position)
{
	m_amountOfZombies--;

	if (m_rng() % 5 != 0) return;

	static const std::vector<std::string> availableGifts =
	{
		GiftData::dmgGift.id,
		GiftData::freezeGift.id,
		GiftData::sunGift.id,
		GiftData::fireRateGift.id,
	};

	const std::string& randomGiftType = availableGifts[m_rng() % availableGifts.size()];

	if (onAddGift)
		onAddGift(position, randomGiftType);
}

void LevelLogicManager::spawnZombie(const std::string& zombieType, const std::string& rowStr) {
	int row;

	if (rowStr == "random")
	{
		static std::uniform_int_distribution<int> rowDistribution(0, Board::ROWS - 1);
		row = rowDistribution(m_rng);
	}
	else
		row = std::stoi(rowStr);

	if (row < 0 || row >= Board::ROWS)
		return;

	onAddZombie({ window::width + 50.f, gridSize::startPos.y - 20 + gridSize::floorSize.y * row }, zombieType);
}

float LevelLogicManager::getProgress() const
{
	return m_levelScripter.getElapsed() / m_levelScripter.getTotalDuration();
}

const std::vector<float>& LevelLogicManager::getFlagPositions() const
{
	return m_levelScripter.getFlagPositions();
}