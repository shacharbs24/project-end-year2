#include "Command/SelectPlantCommand.h"
#include "States/Controller/GameState.h"
#include "Managers/TextureManager.h"
#include "UI/UIManager.h"
#include "Managers/AudioManager.h"

SelectPlantCommand::SelectPlantCommand(UIManager& ui, std::string plantId, const sf::IntRect& rec, std::string textureKey, std::string sound)
	: m_ui(ui), m_plantId(std::move(plantId)), m_rec(rec), m_textureKey(std::move(textureKey)), m_sound(std::move(sound))
{}


void SelectPlantCommand::execute() 
{
    m_ui.selectItem(m_plantId, TextureManager::getInstance().getTexture(m_textureKey), m_rec);
	AudioManager::getInstance().playFx(m_sound);
}