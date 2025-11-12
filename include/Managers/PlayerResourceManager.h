#pragma once
#include <string>

class PlayerResourceManager
{
public:
	explicit PlayerResourceManager(int initialSun = 0);
	void addSun(int amount) { m_sun += amount; }
	int getSun() const { return m_sun; }
	bool buyPlant(const std::string& plantId);
	int getPlantCost(const std::string& plantId) const;

private:
	bool deductSun(int amount);
	int m_sun;
};