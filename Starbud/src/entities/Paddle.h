#pragma once

#include <SFML\Graphics.hpp>
#include "Entity.h"

class Paddle : public Entity
{
public:
	virtual void update(const float dt);
	virtual void handleInput(sf::Event& event);
	virtual void collides(Entity& entity, bool side);

	Paddle(Level* level, float yp, float width);

public:
	float speed;

};