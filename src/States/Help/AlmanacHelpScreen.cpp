#include "States/Help/AlmanacHelpScreen.h"
#include "Managers/TextureManager.h"
#include <Command/CloseInfoCardCommand.h>

AlmanacHelpScreen::AlmanacHelpScreen(StateMachine& machine,
    const std::vector<CardMeta>& cardData,
    std::string barTexture,
    std::string infoTexture,
    std::string hint,
    std::string bgTex)
    : m_machine(machine)
    , m_background(TextureManager::getInstance().getTexture(bgTex))
    , m_hintText()
    , m_closeBtn({ 968.f, 200.f }, { 50.f, 50.f }, "X", 40,
        std::make_unique<CloseInfoCardCommand>(*this))
    , m_cardManager(cardData, barTexture, infoTexture, *this)
{
    m_hintText.setFont(TextureManager::getInstance().getFont("font"));
    m_hintText.setCharacterSize(60);
    m_hintText.setFillColor({ 255, 239, 140 });
    m_hintText.setPosition({ 560.f, 60.f });
    m_hintText.setString(std::move(hint));
    m_closeBtn.setTextColor(sf::Color::Red);
}

void AlmanacHelpScreen::handleEvent(const sf::Event& e)
{
    if (m_cardManager.selectedIndex() >= 0 && e.type == sf::Event::MouseMoved)
        m_closeBtn.handleHover({ float(e.mouseMove.x),float(e.mouseMove.y) });

    m_closeBtn.handleEvent(e);
    m_cardManager.handleEvent(e);
}

void AlmanacHelpScreen::draw(sf::RenderWindow& win) const
{

    win.draw(m_background);
    win.draw(m_hintText);
    m_cardManager.draw(win, m_closeBtn);
}
