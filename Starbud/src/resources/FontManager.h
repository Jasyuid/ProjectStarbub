#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include "../Resources.h"

class FontManager
{
public:
	static void loadFont(const std::string& name, const std::string& path); //Loads font into map
	static sf::Font& getRef(const std::string& key); //Returns font with key
	static void clearFonts();

private:
	static std::map<std::string, sf::Font> fonts; //Font Map

};