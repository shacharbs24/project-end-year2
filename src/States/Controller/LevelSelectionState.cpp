#include "States/Controller/LevelSelectionState.h"
#include "Managers/TextureManager.h"
#include "Command/PushStateCommand.h"
#include "LevelManagment/LevelManager.h"
#include "States/Controller/GameState.h"
#include "Command/PopStateCommand.h"
#include "Managers/AudioManager.h"
#include "Utiles.h"

LevelSelectionState::LevelSelectionState(StateMachine& m) : State(m), m_backButton(m.getBackButton())
{
	m_backgroundSprite.setTexture(TextureManager::getInstance().getTexture("level_selection"));
	syncLevelButtons();
}

void LevelSelectionState::handleEvent(const sf::Event& e)
{
	if (e.type == sf::Event::MouseMoved)
	{
		const sf::Vector2f mousePos = { float(e.mouseMove.x), float(e.mouseMove.y) };
		m_backButton.handleHover(mousePos);
		for (auto& button : m_levelButtons)
		{
			button.handleHover(mousePos);
		}
	}
	m_backButton.handleEvent(e);
	for (auto& button : m_levelButtons)
	{
		button.handleEvent(e);
	}
}

void LevelSelectionState::update(const sf::Time&)
{
	AudioManager::getInstance().playMusic("intro");
	syncLevelButtons();
}

void LevelSelectionState::draw(sf::RenderWindow& win) const
{
	win.draw(m_backgroundSprite);
	for (const auto& button : m_levelButtons)
	{
		button.draw(win);
	}
	m_backButton.draw(win);
}

void LevelSelectionState::syncLevelButtons()
{
	int highestUnlocked = LevelManager::getInstance().getHighestUnlockedLevel();
	int nextLevelToAdd = int(m_levelButtons.size()) + 1;

	for (int lvl = nextLevelToAdd; lvl <= highestUnlocked; ++lvl)
	{
		if (levelScriptExists(lvl))
			createLevelButton(lvl);
	}
}

void LevelSelectionState::createLevelButton(int levelNumber)
{
	if (!levelScriptExists(levelNumber)) return;

	static constexpr int buttonsPerRow = 6;
	static const sf::Vector2f buttonSize = { 100, 100 };
	static const sf::Vector2f startPos = { 305, 300 };
	static constexpr float xSpacing = 145.f;
	static constexpr float ySpacing = 130.f;

	int i = levelNumber;
	int row = (i - 1) / buttonsPerRow;
	int col = (i - 1) % buttonsPerRow;

	sf::Vector2f pos ={	startPos.x + col * xSpacing, startPos.y + row * ySpacing};

	auto cmd = std::make_unique<PushStateCommand<GameState, int>>(m_machine, i);
	m_levelButtons.emplace_back(Button(pos, buttonSize, std::to_string(i), 60, std::move(cmd)));
}