#pragma once
#include "GameObject/Collectable/CollectableObject.h"
#include <Config/GiftData.h>

class UIManager;

class Gift : public CollectableObject {
public:
	Gift(const CreationParams& p, const GiftData::Definition& def);

private:
	void collect() override;

	std::string m_giftType;
	UIManager& m_uiManager;
};

namespace GiftData
{
	inline const std::unordered_map<std::string, sf::IntRect>& iconRectMap()
	{
		static const std::unordered_map<std::string, sf::IntRect> map = {
			{ sunGift.id,      sunGift.spriteDef.rect      },
			{ freezeGift.id,   freezeGift.spriteDef.rect   },
			{ dmgGift.id,      dmgGift.spriteDef.rect      },
			{ fireRateGift.id, fireRateGift.spriteDef.rect }
		};
		return map;
	}

	inline const sf::IntRect& iconRectFor(const std::string& id)
	{
		return iconRectMap().at(id);
	}
}