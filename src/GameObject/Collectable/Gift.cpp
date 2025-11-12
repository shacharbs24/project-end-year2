#include "GameObject/Collectable/Gift.h"
#include "Managers/TextureManager.h"
#include "UI/UIManager.h"

namespace
{
	bool ok =
		GameObject::registerType<Gift>(GiftData::sunGift) &&
		GameObject::registerType<Gift>(GiftData::freezeGift) &&
		GameObject::registerType<Gift>(GiftData::dmgGift) &&
		GameObject::registerType<Gift>(GiftData::fireRateGift);
}

Gift::Gift(const CreationParams& p, const GiftData::Definition& def) :
	CollectableObject(p.position, TextureManager::getInstance().getTexture(def.sheet), def.spriteDef),
	m_giftType(def.id),
	m_uiManager(*p.UIManager)
{
	m_sprite.setTextureRect(def.spriteDef.rect);
	m_sprite.setScale(1.5f, 1.5f);
}

void Gift::collect()
{
	m_uiManager.addGift(m_giftType);
	CollectableObject::collect();
}