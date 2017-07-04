#include "TextureManager.h"

std::map<std::string, sf::Texture> TextureManager::textures;

void TextureManager::loadTexture(const std::string& name, const std::string& path)
{
	sf::Texture tex;
	tex.loadFromFile(TEXTURE_DIRECTORY + path);
	textures[name] = tex;
	return;
}

sf::Texture& TextureManager::getRef(const std::string& key)
{
	return textures.at(key);
}

void TextureManager::clearTextures()
{
	textures.clear();
}
