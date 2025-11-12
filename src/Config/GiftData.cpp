#include "Config/GiftData.h"


namespace GiftID
{
	const std::string freezeGift = "freeze_gift";
	const std::string sunGift = "sun_gift";
	const std::string dmgGift = "dmg_gift";
	const std::string fireRateGift = "fire_rate_gift";
}

namespace FirstSprite
{
	const SpriteDef freezeGift{ {125, 5, 50, 50} };
	const SpriteDef sunGift{ {69, 6, 50, 50} };
	const SpriteDef dmgGift{ {6, 5, 50, 50} };
	const SpriteDef fireRateGift{ {183, 6, 50, 50} };
}

namespace GiftData 
{
	const Definition freezeGift = { GiftID::freezeGift , FirstSprite::freezeGift};
	const Definition sunGift = { GiftID::sunGift, FirstSprite::sunGift };
	const Definition dmgGift = {GiftID::dmgGift, FirstSprite::dmgGift};
	const Definition fireRateGift = {GiftID::fireRateGift, FirstSprite::fireRateGift};
}