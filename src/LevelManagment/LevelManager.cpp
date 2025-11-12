#include "LevelManagment/LevelManager.h"
#include <fstream>
#include <Logger.h>

LevelManager& LevelManager::getInstance()
{
	static LevelManager instance;
	return instance;
}

LevelManager::LevelManager()
{
	loadUnlockedLevel();
}

void LevelManager::loadUnlockedLevel()
{
	std::ifstream file(m_filePath);
	if (!file.is_open()) {
		m_highestLevelUnlocked = 1;
		saveUnlockedLevel();
		return;
	}

	file >> m_highestLevelUnlocked;
	if (file.fail())
	{
		Logger::getInstance().logError("Failed to read from " + m_filePath + ".\n");
		m_highestLevelUnlocked--;
	}
	file.close();
}

void LevelManager::saveUnlockedLevel()
{
	std::ofstream file(m_filePath);
	if (!file.is_open())
	{
		Logger::getInstance().logError("Failed to open " + m_filePath + " for writing.\n");
		return;
	}
	file << m_highestLevelUnlocked;
	file.close();
}

int LevelManager::getHighestUnlockedLevel() const
{
	return m_highestLevelUnlocked;
}

void LevelManager::unlockNextLevel(int currentLevel)
{
	if (currentLevel >= m_highestLevelUnlocked)
	{
		m_highestLevelUnlocked = currentLevel + 1;
		saveUnlockedLevel();
	}
}