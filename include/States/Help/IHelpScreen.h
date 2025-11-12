#pragma once
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

class IHelpScreen {
public:
    virtual ~IHelpScreen() = default;
    virtual void handleEvent(const sf::Event& e) = 0;
    virtual void draw(sf::RenderWindow& win) const = 0;
    virtual void select(int)  {}
    virtual void clearSelection(){}
    virtual std::string hintText() const { return ""; }
    void closeInfoCard() {}
};
