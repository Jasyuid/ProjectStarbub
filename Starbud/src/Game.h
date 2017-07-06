#pragma once

#include <SFML/Graphics.hpp>
#include <stack>
#include <sstream>
#include "Resources.h"
#include "resources\Logger.h"
#include "resources\TextureManager.h"
#include "resources\FontManager.h"
#include "resources\SoundManager.h"
#include "resources\SmartText.h"

class GameState;

class Game 
{
private:
	//Asset Loaders
	void loadTextures();
	void loadAudio();
	void loadFonts();

	void handleInput(GameState* state); //Handles events and single button presses

public:
	Game(); //Creates window, establishes settings, loads assets
	~Game(); //Unloads all states and assets

	GameState* peekState(); //Returns the current state
	void pushState(GameState* state); //Sets the new current state 
	void popState(); //Removes last state
	void changeState(GameState* state); //Replaces current state

	void createDebug();
	void drawDebug();

	void gameLoop(); //Main game loop

	void draw(sf::Drawable& drawable); //Draws object to window

	void setWindowSize(sf::Vector2f size); //Changes window size

private:
	std::stack<GameState*> m_states; //States

	//Debug
	bool debug;
	int fps;
	sf::RectangleShape debugBG;
	sf::Text fpsText;

public:
	sf::RenderWindow m_window; //Main window

	

};