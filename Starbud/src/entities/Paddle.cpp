#include "Paddle.h"

void Paddle::update(const float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		move(sf::Vector2f(-speed*dt, 0));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		move(sf::Vector2f(speed*dt, 0));

	if (getPosition().x < 0) setPosition(sf::Vector2f(0, getPosition().y));
	else if (getPosition().x > APP_WIDTH - getWidth()) setPosition(sf::Vector2f(APP_WIDTH - getWidth(), getPosition().y));
}

void Paddle::handleInput(sf::Event& event)
{

}

void Paddle::collides(Entity& entity, bool side)
{

}

Paddle::Paddle(Level* level, float yp, float width)
{
	this->level = level;
	speed = 300;

	setTexture(TextureManager::getRef("1x1"));
	setScale(width, 8);
	setPosition((APP_WIDTH-getWidth())/2, yp);

}
