#include "Managers/TextureManager.h"
#include "Logger.h"
#include <stdexcept>

TextureManager& TextureManager::getInstance()
{
	static TextureManager instance;
	return instance;
}

sf::Font& TextureManager::getFont(const std::string& name)
{
	const std::string fontName = name + ".ttf";

	if (auto it = m_fonts.find(fontName); it != m_fonts.end())
		return it->second;

	sf::Font font;

	if (!font.loadFromFile(fontName))
		throw std::runtime_error("TextureManager Error: Failed to load font: " + fontName);

	auto [it, _] = m_fonts.emplace(fontName, std::move(font));
	return it->second;
}

sf::Texture& TextureManager::getTexture(const std::string& textureName)
{
	const std::string fileName = textureName + ".png";
	
	if (auto it = m_textures.find(fileName); it != m_textures.end())
		return it->second;

	sf::Texture texture;
	if (!texture.loadFromFile(fileName))
		throw std::runtime_error("TextureManager Error: Failed to load texture: " + fileName);

	auto [it, _] = m_textures.emplace(fileName, std::move(texture));
	return it->second;
}

sf::Image& TextureManager::getIcon()
{
	static sf::Image icon = [] {
		sf::Image img;
		if (!img.loadFromFile("icon.png"))
			throw std::runtime_error("TextureManager Error: Failed to load icon.png");
		return img;
		}();
	return icon;
}
