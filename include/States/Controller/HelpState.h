#pragma once
#include "State.h"
#include "Button/Button.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include <memory>
#include <States/Help/IHelpScreen.h>
#include <functional>

enum class HelpScreen { MAIN, GAMEPLAY, ALMANAC, PLANTS, ZOMBIES, GIFTS };

class StateMachine;

class HelpState : public State {
public:
    explicit HelpState(StateMachine& machine);
    void handleEvent(const sf::Event& e) override;
    void update(const sf::Time&) override {}
    void draw(sf::RenderWindow& win) const override;
    void switchToScreen(HelpScreen screen);
    void select(int index) { if (m_screenHandler) m_screenHandler->select(index);}
    void clearSelection() { if (m_screenHandler) m_screenHandler->clearSelection();}

private:
    void setupButtons();

    HelpScreen m_currentScreen;
    Button& m_backButton;       
    std::unique_ptr<IHelpScreen> m_screenHandler; 

    struct ScreenFactory
    {
        using ScreenCreator = std::function<std::unique_ptr<IHelpScreen>(HelpState&)>;
        ScreenCreator create;
        HelpScreen backTarget;
    };

    static const std::unordered_map<HelpScreen, ScreenFactory>& getScreenFactories();
};
