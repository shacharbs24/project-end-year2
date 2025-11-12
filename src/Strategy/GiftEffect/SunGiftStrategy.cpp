#include "Strategy/GiftEffect/SunGiftStrategy.h"
#include "Managers/PlayerResourceManager.h"

SunGiftStrategy::SunGiftStrategy(PlayerResourceManager& prm)
    : m_prm(prm)
{}

void SunGiftStrategy::applyEffect() 
{
    m_prm.addSun(150);
    play("sun_gift");
}
