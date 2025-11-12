#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "UI/PlantButtons.h"
#include "UI/SunCounter.h"
#include "Button/Button.h"
#include "Managers/TextureManager.h"
#include "UI/ProgressBar.h"
#include "UI/GiftBar.h"

class GameState;
class PlayerResourceManager;
class StateMachine;
class LevelLogicManager;
class GameObjectManager;

class UIManager {
public:
	explicit UIManager(PlayerResourceManager& PlayerResourceManager, StateMachine& stateMachine,
		LevelLogicManager& levelLogicManager, GameObjectManager& objectManager);

	void handleEvent(const sf::Event& e);
	void update(const sf::Time& dt);
	void draw(sf::RenderWindow& window) const;
	void drawText(sf::RenderWindow& window) const;

	void showAnnouncement(const std::string& message);
	void selectItem(const std::string& id, const sf::Texture& tex, const sf::IntRect& rec);
	void cancelSelection();

	bool isPlantSelected() const;
	bool isShovelSelected() const;
	const std::string& getSelectedItem() const;
	void startPlantCooldown(const std::string& plantId);

	void setBackSprite(std::string s) { m_back.setTexture(TextureManager::getInstance().getTexture(std::move(s))); }
	void addGift(const std::string& id);

private:
	void createGameButtons();
	void updatePreviewSpritePosition();

	PlayerResourceManager& m_PlayerResourceManager;
	StateMachine& m_stateMachine;
	LevelLogicManager& m_levelLogicManager;
	GameObjectManager& m_objectManager;

	PlantButtons m_selectionBar;
	SunCounter m_sunCounter;
	std::vector<std::unique_ptr<Button>> m_uiButtons;

	sf::Sprite m_previewSprite;
	std::string m_selectedId;

	sf::Text m_announcementText;
	sf::Clock m_announcementTimer;

	sf::Sprite m_back;

	ProgressBar m_progressBar;
	GiftBar m_giftBar;
};