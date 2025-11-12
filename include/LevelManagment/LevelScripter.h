#pragma once
#include <SFML/System/Time.hpp>
#include <queue>
#include <functional>
#include <string>
#include <vector>
#include <random>

class GameState;
class LevelLogicManager;
class UIManager;
using ParseFn = std::function<void(float&, std::istream&)>;
using ActionMap = std::unordered_map<std::string, ParseFn>;

class LevelScripter
{
public:
	LevelScripter(LevelLogicManager& levelLogicManager, UIManager& ui, int levelNumber);

	void update(const sf::Time& dt);

	float getElapsed() const { return m_elapsed; }
	float getTotalDuration() const { return m_totalDuration; }
	const std::vector<float>& getFlagPositions() const { return m_flagPositions; }

	struct Event
	{
		float time;
		std::function<void()> action;
		bool operator<(const Event& o) const { return time > o.time; }
	};

private:

	LevelLogicManager& m_levelLogicManager;
	UIManager& m_ui;
	float m_elapsed = 0.f;
	std::priority_queue<Event> m_events;
	std::mt19937 m_rng{ std::random_device{}() };
	ActionMap m_actionMap;
	float m_totalDuration = 1.f;
	std::vector<float> m_flagPositions;

	void loadScript(int levelNumber);
	void scheduleGroup(const std::string& row, int count, float interval, const std::vector<std::string>& types);
	void initializeParseTable(int& zombieTotal);
};
