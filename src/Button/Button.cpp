#include "Button/Button.h"
#include "Managers/TextureManager.h"

Button::Button(const sf::Vector2f& pos, const sf::Vector2f& size, std::string label, unsigned charSize, std::unique_ptr<ICommand> cmd)
	: m_shape(size), m_command(std::move(cmd))
{
	m_shape.setPosition(pos);
	m_shape.setFillColor(sf::Color::Transparent);

	m_text.setFont(TextureManager::getInstance().getFont("font"));
	m_text.setString(std::move(label));
	m_text.setCharacterSize(charSize);
	m_text.setFillColor(sf::Color::Black);

	sf::FloatRect textBounds = m_text.getLocalBounds();
	m_text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
	m_text.setPosition(pos + sf::Vector2f(size.x / 2.f, size.y / 2.f));
}

Button::Button(const sf::Sprite& sprite, std::unique_ptr<ICommand> cmd)
	: m_sprite(sprite), m_command(std::move(cmd))
{
	updateShapeFromSprite();
	m_shape.setFillColor(sf::Color::Transparent);
}

Button::Button(const sf::Sprite& sprite, std::unique_ptr<ICommand> cmd, sf::Text txt)
	: m_sprite(sprite), m_command(std::move(cmd)), m_text(std::move(txt))
{
	updateShapeFromSprite();
	m_shape.setFillColor(sf::Color::Transparent);
}

Button::Button(const sf::Vector2f& pos, const sf::Vector2f& size, std::unique_ptr<ICommand> cmd)
	:m_shape(size), m_command(std::move(cmd))
{
	m_shape.setPosition(pos);
	m_shape.setFillColor(sf::Color::Transparent);
}

bool Button::isClicked(const sf::Vector2f& mousePos) const
{
	return isMouseOver(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

bool Button::isMouseOver(const sf::Vector2f& mousePos) const
{
	return m_shape.getGlobalBounds().contains(mousePos);
}

void Button::draw(sf::RenderWindow& w) const
{
	if (m_sprite.getTexture())
		w.draw(m_sprite);
	else
		w.draw(m_shape);

	if (!m_text.getString().isEmpty())
		w.draw(m_text);
}

void Button::handleEvent(const sf::Event& e)
{
	if (e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left)
	{
		if (isMouseOver({ float(e.mouseButton.x), float(e.mouseButton.y) }))
			executeCommand();
	}
}

void Button::executeCommand()
{
	if (m_command)
		m_command->execute();
}

void Button::setTextColor(const sf::Color& color)
{
	if (m_text.getFillColor() != color)
		m_text.setFillColor(color);
}

void Button::setTextureRect(const sf::IntRect& rect)
{
	m_sprite.setTextureRect(rect);
	updateShapeFromSprite();
}

void Button::setPosition(const sf::Vector2f& pos)
{
	m_sprite.setPosition(pos);
	updateShapeFromSprite();

	if (!m_text.getString().isEmpty())
		m_text.setPosition(pos + sf::Vector2f(m_shape.getSize().x / 2.f, m_shape.getSize().y / 2.f));
}

void Button::updateShapeFromSprite()
{
	if (!m_sprite.getTexture()) return;
	const auto texRect = m_sprite.getTextureRect();
	const auto scale = m_sprite.getScale();
	m_shape.setSize({ texRect.width * scale.x, texRect.height * scale.y });
	const auto sprOrigin = m_sprite.getOrigin();
	m_shape.setOrigin(sprOrigin.x * scale.x, sprOrigin.y * scale.y);
	m_shape.setPosition(m_sprite.getPosition());
}