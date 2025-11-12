#pragma once
#include "ICommand.h"
#include <SFML/Graphics.hpp>

class ExitCommand : public ICommand {
public:
    explicit ExitCommand(sf::RenderWindow& window) : m_window(window) {}
    void execute() override { m_window.close();}

private:
    sf::RenderWindow& m_window;
};