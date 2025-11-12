#pragma once
#include "Strategy/GiftEffect/IGiftEffectStrategy.h"

class DamageBoostGiftStrategy : public IGiftEffectStrategy
{
public:
    DamageBoostGiftStrategy(PlayerResourceManager& prm, GameObjectManager& gom);
    void applyEffect() override;

private:
    PlayerResourceManager& m_prm;   
    GameObjectManager& m_gom;
};
