#pragma once
#include "Managers/AudioManager.h"

class PlayerResourceManager;
class GameObjectManager;

class IGiftEffectStrategy {
public:
    virtual ~IGiftEffectStrategy() = default;
    virtual void applyEffect() = 0;

protected:
    void play(std::string s) { AudioManager::getInstance().playFx(std::move(s));}
};
