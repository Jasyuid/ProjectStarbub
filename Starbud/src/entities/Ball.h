#pragma once

#include "../resources/MathHelper.h"
#include "Entity.h"
#include "Paddle.h"
#include "Brick.h"

class Ball : public Entity
{
public:
	virtual void update(const float dt);
	virtual void handleInput(sf::Event& event);
	virtual void collides(Entity& entity, int side);

	Ball(Level* level);

public:
	float angle;
	float speed;
	float hDir;
	float vDir;
	bool hit;

	float startTimer;
	float startDelay;
};