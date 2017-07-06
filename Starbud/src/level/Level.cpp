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
			switch (y)
			{
			case 0:
				addEntity(new Brick(this, (float)(30 * x + 1), (float)(20 * y + 180), sf::Color(205, 0, 0, 255)));
				break;
			case 1:
				addEntity(new Brick(this, (float)(30 * x + 1), (float)(20 * y + 180), sf::Color(205, 205, 0, 255)));
				break;
			case 2:
				addEntity(new Brick(this, (float)(30 * x + 1), (float)(20 * y + 180), sf::Color(0, 205, 0, 255)));
				break;
			case 3:
				addEntity(new Brick(this, (float)(30 * x + 1), (float)(20 * y + 180), sf::Color(0, 205, 205, 255)));
				break;
			case 4:
				addEntity(new Brick(this, (float)(30 * x + 1), (float)(20 * y + 180), sf::Color(205, 0, 205, 255)));
				break;
			}
			
			maxBricks++;
			brickCount++;
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
	lifeScore += amount;
}

void Level::loseLife()
{
	if (lives <= 0) gameover = true;
	else lives-=1;
}

void Level::update(const float dt)
{
	//Gameover and Win menu
	if (gameover || win)
	{
		if (endMenu->action)
		{
			switch (endMenu->selected)
			{
			case 0:
				state->level = new Level(state);
				break;
			case 1:
				game->pushState(new MenuState(game));
				break;
			case 2:
				game->m_window.close();
				break;
			}
		}
		
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
				int side = Collisions::pixelPerfectTest(e, **it2);
				if (side == COL_TOP)
				{
					e.collides(**it2, COL_TOP);
					(**it2).collides(e, COL_BOTTOM);
				}
				else if (side == COL_BOTTOM)
				{
					e.collides(**it2, COL_BOTTOM);
					(**it2).collides(e, COL_TOP);
				}
				else if (side == COL_LEFT)
				{
					e.collides(**it2, COL_LEFT);
					(**it2).collides(e, COL_RIGHT);
				}
				else if (side == COL_RIGHT)
				{
					e.collides(**it2, COL_RIGHT);
					(**it2).collides(e, COL_LEFT);
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

	//SpeedUp
	if (brickCount < 20) ballSpeed = 270;
	else if (brickCount < 40) ballSpeed = 240;
	else if (brickCount < 60) ballSpeed = 210;
	else if (brickCount < 80) ballSpeed = 180;
	else ballSpeed = 150;

	//Life Up
	if (lifeScore >= 2000)
	{
		lives++;
		lifeScore -= 2000;
	}

	if (brickCount <= 0) win = true;

}

void Level::draw(const float dt)
{
	//HUD
	game->draw(hudBGTop);
	game->draw(hudBGBot);

	scoreText.setString("SCORE: " + SmartText::intToString(score));
	game->draw(scoreText);
	timerText.setString("TIME: " + SmartText::intToString((int)timer));
	game->draw(timerText);
	brickText.setString("BRICKS: " + SmartText::intToString(brickCount));
	game->draw(brickText);

	game->draw(lifeText);
	for (int x = 0; x < lives; x++)
	{
		life.setPosition((float)(445 + x * 30), (float)542);
		game->draw(life);
	}

	//Draws entities
	EntityList::iterator it;
	for (it = m_entities.begin(); it != m_entities.end(); it++)
	{
		game->draw(**it);
	}

	//Gameover and Win
	if (gameover)
	{
		game->draw(overlayBG);
		game->draw(scoreText);
		game->draw(timerText);
		game->draw(gameoverText);
		endMenu->draw(dt);
	}
	else if (win)
	{
		game->draw(overlayBG);
		game->draw(scoreText);
		game->draw(timerText);
		game->draw(winText);
		endMenu->draw(dt);
	}
}

void Level::handleInput(sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		if (gameover || win)
		{
			endMenu->handleInput(event);
		}
		break;
	}
}

Level::Level(PlayState* state)
{
	this->state = state;
	game = state->game;

	score = 0;
	brickCount = 0;
	maxBricks = 0;
	lifeScore = 0;
	timer = 0;
	lives = 2;

	gameover = false;
	win = false;

	textCol = sf::Color(255, 255, 255, 255);

	ballSpawnY = 300;
	topBound = 100;
	bottomBound = 500;
	paddleY = 470;

	//HUD
	hudBGTop.setSize(sf::Vector2f(APP_WIDTH, topBound));
	hudBGTop.setFillColor(sf::Color(0, 0, 0, 255));
	hudBGTop.setOutlineColor(sf::Color(255, 255, 255, 255));
	hudBGTop.setOutlineThickness(3);
	hudBGTop.setPosition(sf::Vector2f(0, 0));
	hudBGBot.setSize(sf::Vector2f(APP_WIDTH, APP_HEIGHT - bottomBound));
	hudBGBot.setFillColor(sf::Color(0, 0, 0, 255));
	hudBGBot.setOutlineColor(sf::Color(255, 255, 255, 255));
	hudBGBot.setOutlineThickness(3);
	hudBGBot.setPosition(sf::Vector2f(0, bottomBound));

	SmartText::createText(scoreText, "SCORE: " + SmartText::intToString(score), 32, "pixel", textCol);
	scoreText.setPosition(sf::Vector2f(20, 30));
	SmartText::createText(timerText, "TIME: " + SmartText::intToString((int)timer), 32, "pixel", textCol);
	timerText.setPosition(sf::Vector2f(320, 30));
	SmartText::createText(brickText, "BRICKS: " + SmartText::intToString(brickCount), 32, "pixel", textCol);
	brickText.setPosition(sf::Vector2f(20, 530));

	SmartText::createText(lifeText, "LIVES:", 32, "pixel", textCol);
	lifeText.setPosition(sf::Vector2f(320, 530));
	life.setTexture(TextureManager::getRef("1x1"));
	life.setScale(15, 15);
	life.setColor(sf::Color(255, 255, 255, 255));

	//Win and Gameover
	overlayBG.setFillColor(sf::Color(0, 0, 0, 220));
	overlayBG.setSize(sf::Vector2f(APP_WIDTH, APP_HEIGHT));
	SmartText::createText(gameoverText, "Gameover", 48, "pixel", sf::Color(255, 0, 0, 255));
	gameoverText.setPosition(sf::Vector2f((APP_WIDTH - gameoverText.getLocalBounds().width) / 2, 150));
	SmartText::createText(winText, "Congratulations", 48, "pixel", sf::Color(0, 255, 0, 255));
	winText.setPosition(sf::Vector2f((APP_WIDTH - winText.getLocalBounds().width) / 2, 150));
	SmartText::createText(playText, "Play Again", 32, "roses");
	playText.setPosition(sf::Vector2f((APP_WIDTH - playText.getLocalBounds().width) / 2, 250));
	SmartText::createText(menuText, "Menu", 32, "roses");
	menuText.setPosition(sf::Vector2f((APP_WIDTH - menuText.getLocalBounds().width) / 2, 300));
	SmartText::createText(exitText, "Exit", 32, "roses");
	exitText.setPosition(sf::Vector2f((APP_WIDTH - exitText.getLocalBounds().width) / 2, 350));

	endMenu = new TextMenu(game, sf::Color(255, 255, 255, 255), sf::Color(0, 255, 255, 255));
	endMenu->addItem(playText);
	endMenu->addItem(menuText);
	endMenu->addItem(exitText);

	generateLevel();
}