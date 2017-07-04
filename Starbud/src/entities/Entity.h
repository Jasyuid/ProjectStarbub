#pragma once

#include <SFML/Graphics.hpp>
#include "../resources/Collisions.h"
#include "../level/Level.h"

class Entity : public sf::Sprite
{
public:
	virtual void update(const float dt) = 0;
	virtual void handleInput(sf::Event& event) = 0;

	virtual void collides(Entity& entity, bool side) = 0;

	float getWidth() { return getTextureRect().width * getScale().x; }
	float getHeight() { return getTextureRect().height * getScale().y; }

public:
	Level* level;

	sf::Vector2f pos;

};