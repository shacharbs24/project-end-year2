#include "Strategy/GiftEffect/FireRateGiftStrategy.h"
#include "Managers/GameObjectManager.h"
#include "GameObject/GameObject.h"

FireRateGiftStrategy::FireRateGiftStrategy(PlayerResourceManager& prm, GameObjectManager& gom)
    : m_prm(prm), m_gom(gom)
{}

void FireRateGiftStrategy::applyEffect() 
{
    const float mult = 0.5f;
    const sf::Time dur = sf::seconds(10.f);
    m_gom.forEachInRows([&](GameObject& obj){obj.applyFireRateBoost(mult, dur);});
    play("damage");
}
