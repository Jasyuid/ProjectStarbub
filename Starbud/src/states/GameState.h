#pragma once

#include <iostream>
#include "../Game.h"

class GameState
{
public:
	virtual void update(const float dt) = 0;
	virtual void draw(const float dt) = 0;
	virtual void handleInput(sf::Event& event) = 0;

public:
	Game* game;

};