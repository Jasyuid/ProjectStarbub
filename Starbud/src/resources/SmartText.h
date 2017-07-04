#pragma once

#include <SFML\Graphics.hpp>
#include <sstream>
#include "FontManager.h"

class SmartText
{
public:
	static void createText(sf::Text& text, std::string t, int size, std::string font)
	{
		text.setString(t);
		text.setFont(FontManager::getRef(font));
		text.setCharacterSize(size);
		text.setFillColor(sf::Color(255, 255, 255, 255));
	}

	static void createText(sf::Text& text, std::string t, int size, std::string font, sf::Color col)
	{
		text.setString(t);
		text.setFont(FontManager::getRef(font));
		text.setCharacterSize(size);
		text.setFillColor(col);
	}

	static std::string intToString(int i) //Turns int value into string
	{
		std::ostringstream os;
		os << i;
		return os.str();
	}

};