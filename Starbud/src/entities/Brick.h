#pragma once

#include "Entity.h"
#include "Ball.h"

class Brick : public Entity
{
public:
	virtual void update(const float dt);
	virtual void handleInput(sf::Event& event);
	virtual void collides(Entity& entity, bool side);

	Brick(Level* level, float xp, float yp);

public:
	bool destroyed;
};