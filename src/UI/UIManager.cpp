#include "UI/UIManager.h"
#include "Managers/TextureManager.h"
#include "Command/SelectPlantCommand.h"
#include "Command/PushStateCommand.h"
#include "States/Controller/PauseState.h"
#include "Utiles.h"
#include "Managers/PlayerResourceManager.h"
#include "Managers/LevelLogicManager.h"
#include <Config/GameConfig.h>
#include <Config/PlantData.h>


UIManager::UIManager(PlayerResourceManager& PlayerResourceManager, StateMachine& stateMachine, 
	LevelLogicManager& levelLogicManager ,GameObjectManager& objectManager) :
	m_PlayerResourceManager(PlayerResourceManager), m_stateMachine(stateMachine), 
	m_levelLogicManager(levelLogicManager), m_objectManager(objectManager),
	m_selectionBar(m_PlayerResourceManager,*this),
	m_selectedId(""),
	m_announcementText(createText(72, { 220,20,60 }, sf::Color::Black, 3)),
	m_giftBar(m_PlayerResourceManager, m_objectManager)
{
	createGameButtons();
	m_progressBar.setPosition({ 750, 0 });
}

void UIManager::handleEvent(const sf::Event& e)
{
	m_selectionBar.handleEvent(e);
	m_giftBar.handleEvent(e);

	for (auto& button : m_uiButtons)
	{
		button->handleEvent(e);
	}

	if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Right)
		cancelSelection();
}

void UIManager::update(const sf::Time& dt)
{
	m_selectionBar.update(dt);
	m_sunCounter.update(m_PlayerResourceManager.getSun());
	updatePreviewSpritePosition();
	m_progressBar.update(m_levelLogicManager.getProgress(),m_levelLogicManager.getFlagPositions());
	
	if (m_announcementTimer.getElapsedTime().asSeconds() > 2.5f)
		m_announcementText.setString("");
}

void UIManager::draw(sf::RenderWindow& window) const
{
	window.draw(m_back);
	m_selectionBar.draw(window);
	m_sunCounter.draw(window);
	m_progressBar.draw(window);
	m_giftBar.draw(window);

	for (const auto& button : m_uiButtons)
	{
		button->draw(window);
	}

	if (!m_selectedId.empty())
		window.draw(m_previewSprite);

}

void UIManager::drawText(sf::RenderWindow& window) const
{
	if (!m_announcementText.getString().isEmpty())
	{
		window.draw(m_announcementText);
	}
}

void UIManager::selectItem(const std::string& id, const sf::Texture& tex, const sf::IntRect& rec)
{
	m_selectedId = id;
	if (id.empty()) return;

	m_previewSprite.setTexture(tex);
	m_previewSprite.setTextureRect(rec);
	m_previewSprite.setColor(sf::Color(255, 255, 255, 128));

	constexpr float s = 3.f;
	m_previewSprite.setScale({ s, s });
}


void UIManager::updatePreviewSpritePosition()
{
	if (m_selectedId.empty()) return;

	auto& window = m_stateMachine.getWindow();
	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
	m_previewSprite.setPosition({ worldPos.x - 50.f, worldPos.y - 25.f });
}

void UIManager::showAnnouncement(const std::string& message)
{
	m_announcementText.setString(message);
	sf::FloatRect textRect = m_announcementText.getLocalBounds();
	m_announcementText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_announcementText.setPosition(sf::Vector2f(window::width / 2.0f, 200));
	m_announcementTimer.restart();
}

namespace
{
	std::unique_ptr<Button> createButton(const sf::Vector2f& position, const sf::Vector2f& scale, const std::string& textureName, const sf::IntRect& rec, std::unique_ptr<ICommand> command)
	{
		sf::Sprite sprite(TextureManager::getInstance().getTexture(textureName));
		sprite.setPosition(position);
		sprite.setTextureRect(rec);
		sprite.setScale(scale);
		return std::make_unique<Button>(sprite, std::move(command));
	}
}

void UIManager::createGameButtons()
{
	auto shovelCmd = std::make_unique<SelectPlantCommand>(*this, PlantID::shovel, FirstSprite::shovel.rect, Sheets::shovel, "shovelChoose");
	m_uiButtons.push_back(createButton(
		{ 1200.f, 0.f },
		{ 2.5f, 2.5f },
		Sheets::shovel,
		{ 0, 178, 42, 22 },
		std::move(shovelCmd)
	));

	auto pauseCmd = std::make_unique<PushStateCommand<PauseState, int>>(m_stateMachine, m_levelLogicManager.getLevel());
	m_uiButtons.push_back(createButton(
		{ float(window::width - 96), 0.f },
		{ 3.f, 3.f },
		"other_plants",
		{ 44, 178, 32, 22 },
		std::move(pauseCmd)
	));
}

void UIManager::startPlantCooldown(const std::string& plantId)
{
	m_selectionBar.startPlantCooldown(plantId);
}

void UIManager::addGift(const std::string& id)
{
	m_giftBar.addGiftToInventory(id);
}

bool UIManager::isPlantSelected() const { return !m_selectedId.empty() && m_selectedId != PlantID::shovel; }
bool UIManager::isShovelSelected() const { return m_selectedId == PlantID::shovel; }
const std::string& UIManager::getSelectedItem() const { return m_selectedId; }
void UIManager::cancelSelection() { m_selectedId = ""; }
