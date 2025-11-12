#pragma once
#include "Strategy/GiftEffect/IGiftEffectStrategy.h"


class FireRateGiftStrategy : public IGiftEffectStrategy {
public:
    FireRateGiftStrategy(PlayerResourceManager& prm, GameObjectManager& gom);
    void applyEffect() override;

private:
    PlayerResourceManager& m_prm;
    GameObjectManager& m_gom;
};
