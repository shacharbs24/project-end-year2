#pragma once

#include "ICommand.h"
#include <string>
#include <SFML/Graphics/Rect.hpp>


class GameState;
class UIManager;


class SelectPlantCommand : public ICommand {
public:
    SelectPlantCommand(UIManager& ui, std::string plantId, const sf::IntRect& rec, std::string textureKey, std::string sound = "plantChoose");

    void execute() override;

private:
    UIManager& m_ui;
    std::string m_plantId;
    std::string m_sound;
    sf::IntRect m_rec;
    std::string m_textureKey;
};