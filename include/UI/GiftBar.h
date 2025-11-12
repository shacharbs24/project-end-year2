#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>
#include <unordered_map>

#include "Strategy/GiftEffect/IGiftEffectStrategy.h"
#include "GameObject/Collectable/Gift.h"
#include <vector>

class PlayerResourceManager;
class GameObjectManager;
class Button;

struct GiftSlot
{
	std::string id;
	std::unique_ptr<Button> button;
	size_t count = 1;
	sf::Text counter;
};

class GiftBar
{
public:
	GiftBar(PlayerResourceManager& pmr, GameObjectManager& gom);

	void addGiftToInventory(const std::string& id);

	void activateGift(const std::string& id);

	void handleEvent(const sf::Event& e);
	void update(const sf::Time&);
	void draw(sf::RenderWindow& window) const;

private:
	using StrategyFactory = std::function<std::unique_ptr<IGiftEffectStrategy>()>;
	using StrategyMap = std::unordered_map<std::string, StrategyFactory>;

	PlayerResourceManager& m_PlayerResourceManager;
	GameObjectManager& m_gameObjectManager;

	sf::Sprite m_background;
	sf::Vector2f m_nextGiftSlotPosition{ 350.f, 20.f };
	StrategyMap m_strategies;

	std::vector<GiftSlot> m_giftSlots;
	sf::Font& m_font;

	void updateLayout();
};
