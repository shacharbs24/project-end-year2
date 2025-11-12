#pragma once
#include <SFML/Graphics.hpp>

class StateMachine;

class State {
public:
    virtual ~State() = default;

    virtual void handleEvent(const sf::Event&) = 0;

    virtual void update(const sf::Time&) = 0;

    virtual void draw(sf::RenderWindow&) const = 0;

protected:
    explicit State(StateMachine& machine);

    StateMachine& m_machine;
};
