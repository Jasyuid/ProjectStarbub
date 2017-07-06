#include "Brick.h"

void Brick::update(const float dt)
{

}

void Brick::handleInput(sf::Event& event)
{

}

void Brick::collides(Entity& entity, int side)
{
	if (typeid(entity) == typeid(Ball))
	{
		if (!destroyed) {
			level->addScore(50);
			level->removeEntity(this);
			level->brickCount--;
			destroyed = true;
		}
	}
}

Brick::Brick(Level* level, float xp, float yp, sf::Color& col)
{
	this->level = level;

	destroyed = false;

	setPosition(xp, yp);
	setTexture(TextureManager::getRef("1x1"));
	setColor(col);
	setScale(28, 18);
}