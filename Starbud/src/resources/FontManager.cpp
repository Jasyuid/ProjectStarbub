#include "FontManager.h"

std::map<std::string, sf::Font> FontManager::fonts;

void FontManager::loadFont(const std::string& name, const std::string& path)
{
	sf::Font font;
	font.loadFromFile(FONT_DIRECTORY + path);
	fonts[name] = font;
	return;
}

sf::Font& FontManager::getRef(const std::string& key)
{
	return fonts.at(key);
}

void FontManager::clearFonts()
{
	fonts.clear();
}
