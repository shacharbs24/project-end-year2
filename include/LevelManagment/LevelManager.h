#pragma once

#include <string>

class LevelManager {
public:
	static LevelManager& getInstance();

	void unlockNextLevel(int currentLevel);
	int getHighestUnlockedLevel() const;

private:
	LevelManager();

	void loadUnlockedLevel();
	void saveUnlockedLevel();

	const std::string m_filePath = "Open_Levels.txt";
	int m_highestLevelUnlocked;

	LevelManager(const LevelManager&) = delete;
	LevelManager& operator=(const LevelManager&) = delete;
	LevelManager(LevelManager&&) = delete;
	LevelManager& operator=(LevelManager&&) = delete;
};