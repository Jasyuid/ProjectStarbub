#include "Ball.h"

void Ball::update(const float dt)
{
	if (startTimer < startDelay) {
		startTimer += dt;
		if(startTimer > 2.0) setColor(sf::Color(0, 255, 255, 255));
		else if(startTimer > 1.5) setColor(sf::Color(0, 255, 255, 0));
		else if(startTimer > 1.0) setColor(sf::Color(0, 255, 255, 255));
		else if(startTimer > 0.5) setColor(sf::Color(0, 255, 255, 0));
		return;
	}

	move(speed*cos(Math::degToRad(angle))*dt, vDir*speed*sin(Math::degToRad(angle))*dt);

	if (getPosition().y < level->topBound)
	{
		vDir = 1;
		setPosition(getPosition().x, level->topBound);
	}
	else if (getPosition().x + getWidth() > APP_WIDTH)
	{
		angle = 180 - angle;
		setPosition(APP_WIDTH - getWidth(), getPosition().y);
	}
	else if (getPosition().x < 0)
	{
		angle = 180 - angle;
		setPosition(0, getPosition().y);
	}

	if (getPosition().y + getHeight() > level->bottomBound)
	{
		level->removeEntity(this);
		level->loseLife();
		if(!level->gameover) level->addEntity(new Ball(level));
	}

	hit = false;
}

void Ball::handleInput(sf::Event& event)
{

}

void Ball::collides(Entity& entity, bool side)
{
	if (typeid(entity) == typeid(Paddle))
	{
		if (side) return;
		if (getPosition().y + getHeight() > entity.getPosition().y + entity.getHeight() / 2) return;
		if (getPosition().y + getHeight() - entity.getPosition().y - entity.getHeight()/2 > 0 && vDir == -1) return;
		if (!side) {
			vDir = -1;
			setPosition(getPosition().x, level->paddleY - getHeight());
		}
		float d = (entity.getPosition().x + entity.getWidth() / 2) - (getPosition().x + getWidth() / 2);
		d /= entity.getWidth() / 2;
		angle = 60 * d + 90;
	}
	else if (typeid(entity) == typeid(Brick))
	{
		if (!hit)
		{
			if (!side) vDir = -vDir;
			if (side) angle = 180 - angle;
			hit = true;
		}
	}
	SoundManager::getSoundRef("select").play();
}

Ball::Ball(Level* level)
{
	this->level = level;

	speed = 200;
	angle = 60;
	vDir = 1;
	hit = false;

	startTimer = 0;
	startDelay = 2.5;

	setTexture(TextureManager::getRef("1x1"));
	setScale(5, 5);
	setPosition((APP_WIDTH - getWidth()) / 2, level->ballSpawnY);
	setColor(sf::Color(0, 255, 255, 255));
}
