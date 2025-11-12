#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <array>

class TextureManager {
public:

	static TextureManager& getInstance();
	sf::Font& getFont(const std::string&);
	sf::Texture& getTexture(const std::string& name);
	sf::Image& getIcon();

private:
	TextureManager() = default;

	std::unordered_map<std::string, sf::Font> m_fonts;
	std::unordered_map<std::string, sf::Texture> m_textures;

	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;
	TextureManager(TextureManager&&) = delete;
	TextureManager& operator=(TextureManager&&) = delete;
};
