#pragma once

#include <vector>
#include <algorithm>
#include "../states/GameState.h"
#include "../resources/TextureManager.h"
#include "../resources/FontManager.h"
#include "../resources/SoundManager.h"

class Entity;

class Level
{
public:
	void generateLevel(); //Creates level layout

	void addEntity(Entity* entity);
	void removeEntity(Entity* entity);

	void addScore(int amount);
	void loseLife();

	void update(const float dt); //Updates entities/collision and HUD
	void draw(const float dt); //Draws HUD and entities
	
	Level(Game* game);

private:
	Game* game;
	bool init;

	//HUD
	sf::Sprite hudBGTop, hudBGBot;
	sf::Text scoreText, timerText;
	sf::Color textCol;
	sf::Text lifeText;
	sf::Sprite life;

	//Entities
	typedef std::vector<Entity*> EntityList;
	EntityList m_entities;
	EntityList removeList;
	EntityList addList;

public:
	int score;
	float timer;
	int lives;
	bool gameover;

	float ballSpawnY;
	float topBound, bottomBound;
	float paddleY;

};

