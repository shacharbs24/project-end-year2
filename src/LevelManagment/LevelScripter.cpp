#include "LevelManagment/LevelScripter.h"
#include "Managers/LevelLogicManager.h"
#include "UI/UIManager.h"
#include "LevelManagment/LevelScriptFunctors.h"
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iterator>
#include "Utiles.h"
#include <Logger.h>

LevelScripter::LevelScripter(LevelLogicManager& levelLogicManager, UIManager& ui, int levelNumber) :
	m_levelLogicManager(levelLogicManager), m_ui(ui)
{
	loadScript(levelNumber);
}

void LevelScripter::update(const sf::Time& dt)
{
	m_elapsed += dt.asSeconds();
	while (!m_events.empty() && m_events.top().time <= m_elapsed)
	{
		auto ev = m_events.top();
		m_events.pop();
		ev.action();
	}
}

void LevelScripter::scheduleGroup(const std::string& row, int count, float interval, const std::vector<std::string>& types)
{
	std::uniform_int_distribution<std::size_t> pick(0, types.size() - 1);

	for (int i = 0; i < count; ++i)
	{
		float t = m_elapsed + i * interval;
		std::string type = types[pick(m_rng)];
		m_events.push(Event{
			t,[this, type, row] { m_levelLogicManager.spawnZombie(type, row); } });
	}
}
void LevelScripter::initializeParseTable(int& zombieTotal)
{
	PushEventFn push = [&](const Event& e) { m_events.push(e); };
	LaneCountFn laneCnt = [&]() { return Board::ROWS; };
	ElapsedFn   elapsed = [&]() { return m_elapsed; };

	m_actionMap["WAIT"] = WaitCmd{};
	m_actionMap["CONFIG"] = ConfigCmd{ push, m_levelLogicManager };
	m_actionMap["SPAWN"] = SpawnCmd{ push, m_levelLogicManager, m_rng, laneCnt, &zombieTotal };
	m_actionMap["SPAWN_GROUP"] = SpawnGroupCmd{ push, m_levelLogicManager, m_rng, laneCnt, elapsed, &zombieTotal };
	m_actionMap["ANNOUNCE"] = AnnounceCmd{ push, m_ui };
	m_actionMap["FLAG"] = FlagCmd{ m_flagPositions };
}

void LevelScripter::loadScript(int levelNumber)
{
	std::string path = std::string("level_" + std::to_string(levelNumber) + ".txt");

	std::ifstream in(path);
	if (!in) throw std::runtime_error("Failed to open script file: " + path);

	int zombieTotal = 0;
	float timeline = 0.f;
	initializeParseTable(zombieTotal);

	std::string token;
	while (in >> token)
	{
		if (token.front() == '#')
		{
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		try
		{
			auto it = m_actionMap.find(token);
			if (it == m_actionMap.end())
			{
				throw std::runtime_error(token);
			}
			it->second(timeline, in);
		}
		catch (const std::exception& e)
		{
			Logger::getInstance().logError("Error processing script token '" + token + "'. Details: " + e.what());
			in.clear();
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}

	m_levelLogicManager.setZombieCount(zombieTotal);
	m_totalDuration = timeline;
	for (float& t : m_flagPositions) t /= m_totalDuration;
}