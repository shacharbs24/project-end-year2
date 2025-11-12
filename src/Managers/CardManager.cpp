#include "Managers/CardManager.h"
#include "Managers/TextureManager.h"
#include <Command/SelectAlmanacCommand.h>

CardManager::CardManager(const std::vector<CardMeta>& data,  const std::string barTextureName,  const std::string infoTextureName,  IHelpScreen& helpState)
    : m_data(data)
    , m_barTex(TextureManager::getInstance().getTexture(std::move(barTextureName)))
    , m_infoTex(TextureManager::getInstance().getTexture(std::move(infoTextureName)))
{
    createCards(helpState);
    createInfoSprites();
}

void CardManager::createCards(IHelpScreen& helpState)
{
    m_cards.clear();
    m_cards.reserve(m_data.size());

    for (size_t i = 0; i < m_data.size(); ++i)
    {
        const auto& meta = m_data[i];

        int row = int(i) / PlantAlmanac::cardsPerRow;
        int col = int(i) % PlantAlmanac::cardsPerRow;
        sf::Vector2f pos{
            PlantAlmanac::startPos.x + col * (PlantAlmanac::cardSize + PlantAlmanac::cardSpacing),
            PlantAlmanac::startPos.y + row * (PlantAlmanac::cardSize + PlantAlmanac::cardSpacing)
        };

        sf::Sprite sprite;
        sprite.setTexture(m_barTex);
        sprite.setTextureRect(meta.barRect);
        float scaleX = PlantAlmanac::cardSize / meta.barRect.width;
        float scaleY = PlantAlmanac::cardSize / meta.barRect.height;
        sprite.setScale(scaleX, scaleY);
        sprite.setPosition(pos);

        m_cards.emplace_back(sprite,std::make_unique<SelectAlmanacCommand>(helpState, int(i)));}
}

void CardManager::createInfoSprites()
{
    m_infoSprites.clear();
    m_infoSprites.reserve(m_data.size());

    for (const auto& meta : m_data)
    {
        sf::Sprite s;
        s.setTexture(m_infoTex);
        s.setTextureRect(meta.infoRect);
        s.setPosition(PlantAlmanac::selectedPlantPos);
        m_infoSprites.push_back(std::move(s));
    }
}

void CardManager::handleEvent(const sf::Event& e)
{
    for (auto& btn : m_cards)
        btn.handleEvent(e);
}

void CardManager::draw(sf::RenderWindow& win, const Button& closeBtn) const
{
    for (const auto& btn : m_cards)
        btn.draw(win);

    if (m_selected >= 0 && m_selected < int(m_infoSprites.size()))
    {
        win.draw(m_infoSprites[m_selected]);
        closeBtn.draw(win);
    }
}

void CardManager::select(int index)
{
    if (index >= 0 && index < int(m_data.size()))
        m_selected = index;
}

