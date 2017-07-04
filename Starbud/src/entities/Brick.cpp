#include "Brick.h"

void Brick::update(const float dt)
{

}

void Brick::handleInput(sf::Event& event)
{

}

void Brick::collides(Entity& entity, bool side)
{
	if (typeid(entity) == typeid(Ball))
	{
		if (!destroyed) {
			level->addScore(50);
			level->removeEntity(this);
			destroyed = true;
		}
	}
}

Brick::Brick(Level* level, float xp, float yp)
{
	this->level = level;

	destroyed = false;

	setPosition(xp, yp);
	setTexture(TextureManager::getRef("1x1"));
	setColor(sf::Color(255, 0, 0, 255));
	setScale(28, 18);
}