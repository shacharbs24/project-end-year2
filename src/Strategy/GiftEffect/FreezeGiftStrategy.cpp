#include "Strategy/GiftEffect/FreezeGiftStrategy.h"
#include "Managers/GameObjectManager.h"
#include "GameObject/GameObject.h"

FreezeGiftStrategy::FreezeGiftStrategy(GameObjectManager& gom) : m_gom(gom)
{}

void FreezeGiftStrategy::applyEffect()
{
    const sf::Time freezeDuration = sf::seconds(7.f);
    m_gom.forEachInRows([&](GameObject& obj){obj.applyFreezeEffect(freezeDuration);});
    play("freeze");
}
