#pragma once
#include "Strategy/GiftEffect/IGiftEffectStrategy.h"

class SunGiftStrategy : public IGiftEffectStrategy {
public:
    SunGiftStrategy(PlayerResourceManager& prm);  
    void applyEffect() override;

private:
    PlayerResourceManager& m_prm;
};
