#pragma once

#include <vector>
#include <algorithm>
#include "../states/PlayState.h"
#include "../resources/TextureManager.h"
#include "../resources/FontManager.h"
#include "../resources/SoundManager.h"
#include "../gui/TextMenu.h"

class Entity;
class PlayState;

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
	
	void handleInput(sf::Event& event);

	Level(PlayState* state);

private:
	Game* game;
	PlayState* state;
	bool init;

	//HUD
	sf::RectangleShape hudBGTop, hudBGBot;
	sf::Text scoreText, timerText, brickText;
	sf::Color textCol;
	sf::Text lifeText;
	sf::Sprite life;

	//Entities
	typedef std::vector<Entity*> EntityList;
	EntityList m_entities;
	EntityList removeList;
	EntityList addList;

	//Win and Gameover
	sf::RectangleShape overlayBG;
	sf::Text gameoverText, winText;
	TextMenu* endMenu;
	sf::Text playText, menuText, exitText;

public:
	int score;
	int brickCount;
	int maxBricks;
	float timer;
	float ballSpeed;
	int lifeScore;
	int lives;
	bool gameover;
	bool win;

	float ballSpawnY;
	float topBound, bottomBound;
	float paddleY;

};

