#include "Managers/PlayerResourceManager.h"
#include "UI/PlantButtons.h" 
#include <unordered_map>

PlayerResourceManager::PlayerResourceManager(int initialSun) : m_sun(initialSun) {}


bool PlayerResourceManager::deductSun(int amount)
{
    if (m_sun >= amount)
    {
        m_sun -= amount;
        return true;
    }
    return false;
}

int PlayerResourceManager::getPlantCost(const std::string& plantId) const
{
    static const std::unordered_map<std::string, int> plantCosts = PlantButtons::createCostMap();
    return plantCosts.at(plantId);
}


bool PlayerResourceManager::buyPlant(const std::string& plantId)
{
    return deductSun(getPlantCost(plantId));
}