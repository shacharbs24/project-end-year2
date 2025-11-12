#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <vector>
#include "Button/Button.h"
#include "Config/AlmanacData.h"
#include "IHelpScreen.h"
#include "Managers/CardManager.h"

class StateMachine;

class AlmanacHelpScreen : public IHelpScreen {
public:
    AlmanacHelpScreen(StateMachine& machine, const std::vector<CardMeta>& cardData, std::string barTexture, 
        std::string infoTexture, std::string hint, std::string bgTex);

    ~AlmanacHelpScreen() override = default;

    void handleEvent(const sf::Event& e) override;
    void draw(sf::RenderWindow& win) const override;
    void select(int idx) override { m_cardManager.select(idx); }
    void clearSelection() override { m_cardManager.clearSelection(); }
    std::string hintText() const override { return m_hintText.getString(); }

protected:
    StateMachine& m_machine;
    CardManager m_cardManager;
    Button m_closeBtn;
    sf::Sprite m_background;
    sf::Text m_hintText;
};