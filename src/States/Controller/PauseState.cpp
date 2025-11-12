#include "States/Controller/PauseState.h"
#include "States/Controller/StateMachine.h"
#include "Managers/TextureManager.h"
#include "Command/PopStateCommand.h"
#include "Command/PushStateCommand.h"
#include "Command/ExitCommand.h"
#include "States/Controller/HelpState.h"
#include "Managers/AudioManager.h"
#include <Command/RestartLevelCommand.h>
#include <Config/GameConfig.h>

namespace
{
	struct MenuItemCfg
	{
		std::string label;
		std::function<std::unique_ptr<ICommand>()> makeCmd;
	};

	const sf::Vector2f ButtonScale = { 10.f, 4.f };
	const sf::IntRect ButtonRect = { 85, 178, 32, 24 };
	constexpr float FirstBtnY = 320.f;
	constexpr float BtnSpacingY = 100.f;

	sf::Text makeMenuLabel(const std::string& str, const sf::Vector2f& pos)
	{
		sf::Text txt = createText(40, sf::Color::Black, sf::Color::Transparent, 0.f, TextureManager::getInstance().getFont("font"));
		txt.setString(str);
		centerOrigin(txt);
		txt.setPosition(pos);
		return txt;
	}
}

PauseState::PauseState(StateMachine& m, int level) : State(m), m_level(level), m_font(TextureManager::getInstance().getFont("font"))
{
	setupUI();
	AudioManager::getInstance().playFx("pause");
}

void PauseState::createButton(const std::string& label,
	std::unique_ptr<ICommand> cmd,
	const sf::Vector2f& pos)
{
	static const sf::Texture& tex = TextureManager::getInstance().getTexture("other_plants");
	sf::Sprite spr(tex);
	spr.setTextureRect(ButtonRect);
	spr.setOrigin(ButtonRect.width / 2.f, ButtonRect.height / 2.f);
	spr.setScale(ButtonScale);
	spr.setPosition(pos);
	m_buttons.emplace_back(Button(spr, std::move(cmd), makeMenuLabel(label, pos)));
}

void PauseState::setupUI()
{
	m_background.setSize({ float(window::width),float(window::height) });
	m_background.setFillColor(sf::Color(0, 0, 0, 150));
	m_pausedText = createText(80, sf::Color::White, sf::Color::Transparent, 0.f, m_font);
	m_pausedText.setString("Paused");
	centerOrigin(m_pausedText);
	m_pausedText.setPosition(window::width / 2.f, 150.f);

	const std::array<MenuItemCfg, 5> items{
		MenuItemCfg{ "Resume",			[this] { return std::make_unique<PopStateCommand>(m_machine); } },
		MenuItemCfg{ "Restart Level",	[this] { return std::make_unique<RestartLevelCommand>(m_machine, m_level); } },
		MenuItemCfg{ "Help",			[this] { return std::make_unique<PushStateCommand<HelpState>>(m_machine); } },
		MenuItemCfg{ "Forfeit Level",	[this] { return std::make_unique<PopStateCommand>(m_machine, 2); } },
		MenuItemCfg{ "Exit Game",		[this] { return std::make_unique<ExitCommand>(m_machine.getWindow()); } },
	};

	m_buttons.clear();

	for (size_t i = 0; i < items.size(); ++i)
	{
		const sf::Vector2f pos = { window::width / 2.f, FirstBtnY + i * BtnSpacingY };
		createButton(items[i].label, items[i].makeCmd(), pos);
	}
}

void PauseState::handleEvent(const sf::Event& e)
{
	if (e.type == sf::Event::MouseMoved)
	{
		sf::Vector2f mousePos(float(e.mouseMove.x), float(e.mouseMove.y));

		for (size_t i = 0; i < m_buttons.size(); ++i)
		{
			m_buttons[i].handleHover({ float(e.mouseMove.x), float(e.mouseMove.y) });
		}
	}

	for (auto& button : m_buttons)
	{
		button.handleEvent(e);
	}
}

void PauseState::draw(sf::RenderWindow& win) const
{
	m_machine.drawPrevState(win);
	win.draw(m_background);
	win.draw(m_pausedText);

	for (const auto& button : m_buttons)
	{
		button.draw(win);
	}
}