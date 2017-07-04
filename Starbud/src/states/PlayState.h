#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include "GameState.h"
#include "MenuState.h"
#include "../resources/Logger.h"
#include "../level/Level.h"
#include "../gui/TextMenu.h"
#include "../resources/SmartText.h"

class PlayState : public GameState
{
public:
	virtual void update(const float dt);
	virtual void draw(const float dt);
	virtual void handleInput(sf::Event& event);

	PlayState(Game* game);

private:
	sf::View view;

	Level* level;

	sf::RectangleShape gameoverBG;
	sf::Text gameoverText;
	TextMenu* gameoverMenu;
	sf::Text playText, menuText, exitText;

};