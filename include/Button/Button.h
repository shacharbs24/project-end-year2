#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <Command/ICommand.h>

class Button {
public:
	Button(const sf::Vector2f& pos, const sf::Vector2f& size, std::string label, unsigned charSize, std::unique_ptr<ICommand> cmd);
	Button(const sf::Sprite& sprite, std::unique_ptr<ICommand> cmd);
	Button(const sf::Sprite& sprite, std::unique_ptr<ICommand> cmd, sf::Text txt);
	Button(const sf::Vector2f& pos, const sf::Vector2f& size, std::unique_ptr<ICommand> cmd);

	void draw(sf::RenderWindow& w) const;

	void handleEvent(const sf::Event& e);

	bool isMouseOver(const sf::Vector2f& mousePos) const;

	bool isClicked(const sf::Vector2f& mousePos) const;

	void setTextColor(const sf::Color& color);

	void setSpriteColor(const sf::Color& c) { m_sprite.setColor(c); }

	void executeCommand();

	void setCommand(std::unique_ptr<ICommand> cmd) { m_command = std::move(cmd); }

	void setPosition(const sf::Vector2f& pos);

	void setTextureRect(const sf::IntRect& rect);

	void handleHover(const sf::Vector2f& mousePos) { setTextColor(isMouseOver(mousePos) ? sf::Color::Red : sf::Color::Black); }

private:
	sf::RectangleShape m_shape;
	sf::Text m_text;
	sf::Sprite m_sprite;
	std::unique_ptr<ICommand> m_command;

	void updateShapeFromSprite();
};