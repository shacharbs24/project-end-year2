#pragma once

#include <SFML/Graphics.hpp>

class Animation
{
public:
    void setup(const sf::IntRect& baseRect, int frameCount, float switchTime, float offset = 0, bool loop = true);
    void update(float deltaTime);
    bool isDone() const;

    sf::IntRect uvRect;
private:

    sf::IntRect m_baseRect;   
    int m_frameCount = 0;         
    int m_currentFrame = 0;      
    float m_totalTime = 0;        
    float m_switchTime = 0;
    float m_offset = 0;
    bool m_loop = true;
    int m_stride = 0;
};