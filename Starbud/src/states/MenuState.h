#pragma once

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "../resources/SmartText.h"
#include "../gui/TextMenu.h"

class MenuState : public GameState
{
public:
	virtual void update(const float dt);
	virtual void draw(const float dt);
	virtual void handleInput(sf::Event& event);

	MenuState(Game* game);

private:
	sf::View view;

	sf::Text titleText;
	sf::Text baseText;
	
	TextMenu* menu;
	sf::Text playText;
	sf::Text exitText;
};
