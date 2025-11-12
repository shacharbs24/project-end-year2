#pragma once
#include "Strategy/GiftEffect/IGiftEffectStrategy.h"

class FreezeGiftStrategy : public IGiftEffectStrategy
{
public:
    FreezeGiftStrategy(GameObjectManager& gom);
    void applyEffect() override;

private:
    GameObjectManager& m_gom;
};
