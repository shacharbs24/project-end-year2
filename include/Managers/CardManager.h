#pragma once
#include "Button/Button.h"
#include <vector>
#include <string>
#include "Managers/TextureManager.h"
#include <Command/SelectAlmanacCommand.h>
#include "Config/AlmanacData.h"
#include "States/Help/IHelpScreen.h"

class HelpState;

struct CardData {
	std::string id;
	sf::IntRect infoRect;
};

class CardManager {
public:

	CardManager(const std::vector<CardMeta>& data, std::string barTextureName, std::string infoTextureName, IHelpScreen& helpState);

	void handleEvent(const sf::Event& e);
	void draw(sf::RenderWindow& win, const Button& closeBtn) const;

	void select(int index);
	void clearSelection() { m_selected = -1; }
	int selectedIndex() const { return m_selected; }

private:
	const std::vector<CardMeta>& m_data;
	const sf::Texture& m_barTex;
	const sf::Texture& m_infoTex;

	std::vector<Button> m_cards;
	std::vector<sf::Sprite> m_infoSprites;
	int m_selected = 0;

	void createCards(IHelpScreen& helpState);
	void createInfoSprites();
};
