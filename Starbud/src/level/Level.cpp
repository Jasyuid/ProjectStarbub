#include "Level.h"

#include "../entities/Ball.h"
#include "../entities/Brick.h"
#include "../entities/Paddle.h"

void Level::generateLevel()
{
	for (int x = 0; x < 20; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			addEntity(new Brick(this, 30*x + 1, 20*y + 180));
		}
	}
	
	addEntity(new Paddle(this, paddleY, 50));
	addEntity(new Ball(this));

	init = true;
}

void Level::addEntity(Entity* entity)
{
	if(init) addList.push_back(entity);
	else m_entities.push_back(entity);
}

void Level::removeEntity(Entity* entity)
{
	removeList.push_back(entity);
}

void Level::addScore(int amount)
{
	score += amount;
}

void Level::loseLife()
{
	if (lives <= 0) gameover = true;
	else lives-=1;
}

void Level::update(const float dt)
{
	if (gameover)
	{
		return;
	}

	//Entity updates
	EntityList::iterator it, it2;
	for (it = m_entities.begin(); it != m_entities.end(); it++)
	{
		Entity& e = **it;
		e.update(dt);

		//Collision betweeen entities
		if (typeid(e) == typeid(Paddle) || typeid(e) == typeid(Ball))
		{
			for (it2 = m_entities.begin(); it2 != m_entities.end(); it2++)
			{
				if (typeid(e) == typeid(**it2)) continue;
				Collisions::Side side = Collisions::pixelPerfectTest(e, **it2);
				if (side == Collisions::Side::HORIZONTAL)
				{
					e.collides(**it2, true);
					(**it2).collides(e, true);
				}
				else if (side == Collisions::Side::VERTICAL)
				{
					e.collides(**it2, false);
					(**it2).collides(e, false);
				}
			}
		}
	}

	//Add and Remove Entities
	for (it = addList.begin(); it != addList.end(); it++)
	{
		m_entities.push_back(*it);
	}
	addList.clear();

	for (it = removeList.begin(); it != removeList.end(); it++)
	{
		m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), *it), m_entities.end());
	}
	removeList.clear();

	//Timer
	timer += dt;
}

void Level::draw(const float dt)
{
	//HUD
	game->draw(hudBGTop);
	game->draw(hudBGBot);

	scoreText.setString("Score: " + SmartText::intToString(score));
	game->draw(scoreText);
	timerText.setString("Time: " + SmartText::intToString((int)timer));
	game->draw(timerText);

	game->draw(lifeText);
	for (int x = 0; x < lives; x++)
	{
		life.setPosition(425 + x * 30, 32);
		game->draw(life);
	}

	//Draws entities
	EntityList::iterator it;
	for (it = m_entities.begin(); it != m_entities.end(); it++)
	{
		game->draw(**it);
	}

	if (gameover)
	{

	}
}

Level::Level(Game* game)
{
	this->game = game;

	score = 0;
	timer = 0;
	lives = 3;
	gameover = false;

	textCol = sf::Color(255, 255, 255, 255);

	ballSpawnY = 300;
	topBound = 100;
	bottomBound = 500;
	paddleY = 470;

	//HUD
	hudBGTop.setTexture(TextureManager::getRef("1x1"));
	hudBGTop.setScale(sf::Vector2f(APP_WIDTH, topBound));
	hudBGTop.setColor(sf::Color(0, 0, 100, 255));
	hudBGTop.setPosition(sf::Vector2f(0, 0));
	hudBGBot.setTexture(TextureManager::getRef("1x1"));
	hudBGBot.setScale(sf::Vector2f(APP_WIDTH, APP_HEIGHT - bottomBound));
	hudBGBot.setColor(sf::Color(0, 0, 100, 255));
	hudBGTop.setPosition(sf::Vector2f(0, bottomBound));

	SmartText::createText(scoreText, "Score: " + SmartText::intToString(score), 32, "pixel", textCol);
	scoreText.setPosition(sf::Vector2f(20, 20));
	SmartText::createText(timerText, "Time: " + SmartText::intToString(timer), 32, "pixel", textCol);
	timerText.setPosition(sf::Vector2f(20, 550));

	SmartText::createText(lifeText, "Lives:", 32, "pixel", textCol);
	lifeText.setPosition(sf::Vector2f(300, 20));
	life.setTexture(TextureManager::getRef("1x1"));
	life.setScale(15, 15);
	life.setColor(sf::Color(0, 255, 255, 255));

	generateLevel();
}