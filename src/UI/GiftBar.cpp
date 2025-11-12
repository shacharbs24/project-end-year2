#include "UI/GiftBar.h"
#include "Managers/TextureManager.h"
#include "Command/ActivateGiftCommand.h"
#include "Strategy/GiftEffect/FireRateGiftStrategy.h"
#include "Strategy/GiftEffect/DamageBoostGiftStrategy.h"
#include "Strategy/GiftEffect/FreezeGiftStrategy.h"
#include "Strategy/GiftEffect/SunGiftStrategy.h"
#include "Button/Button.h"
#include <iostream>
#include "Utiles.h"


namespace 
{
    inline static const sf::Vector2f CellSize{ 58.f, 58.f };
    inline static const sf::Vector2f InnerOffs{ 18.f, 25.f };
    inline static constexpr float Gap = 10.f;
    inline static constexpr unsigned MaxSlots = 4;

    static sf::Vector2f slotPosition(const sf::Vector2f& bgPos, size_t index)
    {
        size_t col = index % MaxSlots;
        size_t row = index / MaxSlots;
        return
        {
            10.f + bgPos.x + InnerOffs.x + float(col) * (CellSize.x + Gap),
            bgPos.y + InnerOffs.y + float(row) * (CellSize.y + Gap)
        };
    }

}

GiftBar::GiftBar(PlayerResourceManager& pmr, GameObjectManager& gom)
    : m_PlayerResourceManager(pmr)
    , m_gameObjectManager(gom)
	, m_font(TextureManager::getInstance().getFont("font"))
{
    m_background.setTexture(TextureManager::getInstance().getTexture("gifts"));
	m_background.setTextureRect({ 1, 66, 320, 170 });
    m_background.setPosition({ 350.f, 0.f });
   
    m_strategies.emplace(GiftData::fireRateGift.id, [this] {
        return std::make_unique<FireRateGiftStrategy>(m_PlayerResourceManager, m_gameObjectManager);
        });
    m_strategies.emplace(GiftData::dmgGift.id, [this] {
        return std::make_unique<DamageBoostGiftStrategy>(m_PlayerResourceManager, m_gameObjectManager);
        });
    m_strategies.emplace(GiftData::freezeGift.id, [this] {
        return std::make_unique<FreezeGiftStrategy>(m_gameObjectManager);
        });
    m_strategies.emplace(GiftData::sunGift.id, [this] {
        return std::make_unique<SunGiftStrategy>(m_PlayerResourceManager);
        });
    m_giftSlots.reserve(MaxSlots);

}

void GiftBar::updateLayout()
{
    for (size_t i = 0; i < m_giftSlots.size(); ++i)
    {
        auto pos = slotPosition(m_background.getPosition(),i);
        m_giftSlots[i].button->setPosition(pos);
        m_giftSlots[i].counter.setPosition(pos.x + 20, pos.y + CellSize.y - 15);
    }
}
void GiftBar::activateGift(const std::string& id)
{
  
    if (auto it = m_strategies.find(id); it != m_strategies.end())
        it->second()->applyEffect();
 
    for (size_t i = 0; i < m_giftSlots.size(); ++i)
    {
        if (m_giftSlots[i].id == id)
        {
            if (--m_giftSlots[i].count == 0)
                m_giftSlots.erase(m_giftSlots.begin() + i);
            else
                m_giftSlots[i].counter.setString(std::to_string(m_giftSlots[i].count));
            break;
        }
    }
    updateLayout();         
}


void GiftBar::addGiftToInventory(const std::string& id)
{

    for (auto& slot : m_giftSlots)
    {
        if (slot.id == id)
        {
            ++slot.count;
            slot.counter.setString(std::to_string(slot.count));
            return;
        }
    }

    if (m_giftSlots.size() == MaxSlots) return;

    m_giftSlots.emplace_back();
    GiftSlot& slot = m_giftSlots.back();

    slot.id = id;
    slot.count = 1;

    sf::Vector2f pos = slotPosition(m_background.getPosition(),(m_giftSlots.size() - 1));

    sf::Sprite icon(TextureManager::getInstance().getTexture("gifts"));
    icon.setTextureRect(GiftData::iconRectFor(id));
    icon.setPosition(pos);
    icon.setScale({ 1.10f, 1.10f });

    slot.button = std::make_unique<Button>(icon,std::make_unique<ActivateGiftCommand>(*this, id));

	slot.counter = createText(25, sf::Color::White,sf::Color::Transparent, 0.f,m_font );
    slot.counter.setString("1");
    slot.counter.setPosition(pos.x + 20, pos.y + CellSize.y - 10);

    updateLayout(); 
}


void GiftBar::handleEvent(const sf::Event& e)
{
    for (size_t i = 0; i < m_giftSlots.size(); ++i)
    {
        m_giftSlots[i].button->handleEvent(e);
    }
}


void GiftBar::update(const sf::Time& ){}

void GiftBar::draw(sf::RenderWindow& window) const
{
    window.draw(m_background);
    for (size_t i = 0; i < m_giftSlots.size(); ++i)
    {
        m_giftSlots[i].button->draw(window);
        window.draw(m_giftSlots[i].counter);
    }
}