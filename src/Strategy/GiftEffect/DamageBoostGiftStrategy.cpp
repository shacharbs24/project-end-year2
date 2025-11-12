#include "Strategy/GiftEffect/DamageBoostGiftStrategy.h"
#include "Managers/AudioManager.h"
#include "Managers/GameObjectManager.h"
#include "GameObject/GameObject.h"
#include "Strategy/Effects/DamageEffect.h"

DamageBoostGiftStrategy::DamageBoostGiftStrategy(PlayerResourceManager& prm, GameObjectManager& gom)
    : m_prm(prm), m_gom(gom)
{}

void DamageBoostGiftStrategy::applyEffect()
{
    const float boostMultiplier = 1.5f;
    const sf::Time  boostDuration = sf::seconds(10.f);
    DamageEffect::startGlobalBoost(boostMultiplier, boostDuration);

    m_gom.forEachInRows([&](GameObject& obj){obj.applyDamageBoost(boostMultiplier, boostDuration);});
    play("damage");
}
