#pragma once

#include <vector>
#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../resources/SoundManager.h"
#include "../Game.h"

class TextMenu
{
public:
	void addItem(sf::Text& text); //Add a text item to the menu

	void selectDown(); //Move selector down
	void selectUp(); //Move selector up

	void draw(const float dt); //Draw menu items

	TextMenu(Game* game, sf::Color& off, sf::Color& on);
	
private:
	Game* game;

	sf::Color off, on;
	sf::Sound select;
	std::vector<sf::Text> textItems;

public:
	int selected;

};