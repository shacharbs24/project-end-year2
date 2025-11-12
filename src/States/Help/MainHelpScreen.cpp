#include "States/Help/MainHelpScreen.h"
#include "States/Controller/HelpState.h"
#include "Managers/TextureManager.h"
#include "Command/SwitchHelpScreenCommand.h"

MainHelpScreen::MainHelpScreen(HelpState& helpState)
	: m_helpState(helpState)
{
	m_background.setTexture(TextureManager::getInstance().getTexture("help_back"));
	setup();
}

void MainHelpScreen::setup()
{
	const auto& texture = TextureManager::getInstance().getTexture("help_buttons");

	sf::Sprite gameplaySprite(texture);
	gameplaySprite.setTextureRect({ 12, 445, 420, 150 });
	gameplaySprite.setPosition(300.f, 400.f);
	m_buttons.emplace_back(gameplaySprite, std::make_unique<SwitchHelpScreenCommand>(m_helpState, HelpScreen::GAMEPLAY));

	sf::Sprite almanacSprite(texture);
	almanacSprite.setTextureRect({ 4, 10, 360, 355 });
	almanacSprite.setPosition(900.f, 320.f);
	m_buttons.emplace_back(almanacSprite, std::make_unique<SwitchHelpScreenCommand>(m_helpState, HelpScreen::ALMANAC));

	m_buttons.back().setTextColor({ 255, 239, 140 });
}

void MainHelpScreen::handleEvent(const sf::Event& e)
{
	if (e.type == sf::Event::MouseMoved)
	{
		sf::Vector2f mousePos(static_cast<float>(e.mouseMove.x), static_cast<float>(e.mouseMove.y));
		for (auto& btn : m_buttons)
		{
			btn.setSpriteColor(btn.isMouseOver(mousePos) ? sf::Color(255, 255, 255, 200) : sf::Color::White);
		}
	}

	for (auto& btn : m_buttons)
	{
		btn.handleEvent(e);
	}
}

void MainHelpScreen::draw(sf::RenderWindow& win) const
{
	win.draw(m_background);
	for (const auto& btn : m_buttons)
	{
		btn.draw(win);
	}
}