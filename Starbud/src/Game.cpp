#include "Game.h"

#include "states\GameState.h"

Game::Game()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 1;

	m_window.create(sf::VideoMode(APP_WIDTH, APP_HEIGHT), APP_TITLE, sf::Style::Close, settings);
	m_window.setKeyRepeatEnabled(false);
	m_window.requestFocus();

	loadTextures();
	loadAudio();
	loadFonts();

	createDebug();
	debug = false;

	//SoundManager::setSoundVolume(0);
}

Game::~Game() 
{
	TextureManager::clearTextures();
	FontManager::clearFonts();
	SoundManager::clearBuffers();
	while (!m_states.empty()) popState();
}

void Game::loadTextures()
{
	TextureManager::loadTexture("1x1", "1x1.png");
	TextureManager::loadTexture("test", "test.png");
}

void Game::loadAudio()
{
	SoundManager::loadSound("select", "select.wav");

	SoundManager::loadMusic("test", "testsong.wav");
}

void Game::loadFonts()
{
	FontManager::loadFont("aw", "Audiowide-Regular.ttf");
	FontManager::loadFont("pixel", "PixelSplitter-Bold.ttf");
	FontManager::loadFont("roses", "RosesareFF0000.ttf");
}


void Game::pushState(GameState* state)
{
	m_states.push(state);
	return;
}

void Game::popState()
{
	delete m_states.top();
	m_states.pop();
	return;
}

void Game::changeState(GameState* state)
{
	if (!m_states.empty())
		popState();
	pushState(state);
}

GameState* Game::peekState()
{
	if (m_states.empty()) return nullptr;
	return m_states.top();
}

void Game::handleInput(GameState* state)
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;
		case sf::Event::KeyPressed:
			//DO NOT BREAK HERE TO ALLOW KEY PRESSSES IN OTHER CLASSES
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				m_window.close();
				break;
			case sf::Keyboard::LControl:
				//Debug
				debug = !debug;
				if (debug)
				{
					LOG("Debug panel activated");
				}
				else
				{
					LOG("Debug panel deactivated");
				}
				break;
			case sf::Keyboard::Tab:
				setWindowSize(sf::Vector2f(900, 900));
				break;
			}
		default:
			state->handleInput(event);
			break;
		}
	}
}

void Game::createDebug()
{
	debugBG.setFillColor(sf::Color(0, 0, 0, 200));
	debugBG.setSize(sf::Vector2f(APP_WIDTH, 50));

	SmartText::createText(fpsText, "FPS: " + SmartText::intToString(fps), 16, "roses");
	fpsText.setPosition(sf::Vector2f(5, 5));
}

void Game::drawDebug()
{
	draw(debugBG);	
	fpsText.setString("FPS: " + SmartText::intToString(fps));
	draw(fpsText);
}

void Game::gameLoop() 
{
	sf::Clock clock;
	float totalElapsed = 0.0f;
	int frames = 0;

	while (m_window.isOpen())
	{
		sf::Time elapsed = clock.restart();
		float dt = elapsed.asSeconds();

		//Update and Render
		if (peekState() == nullptr) continue;
		handleInput(peekState());
		peekState()->update(dt);
		this->m_window.clear(sf::Color::Black);
		peekState()->draw(dt);
		if (debug) drawDebug();
		this->m_window.display();
		
		//FPS Counter
		totalElapsed += dt;
		frames++;
		if (totalElapsed > 1.0f)
		{
			LOGC("FPS: " << frames, 3);
			fps = frames;
			totalElapsed -= 1.0f;
			frames = 0;
		}
	}
}

void Game::draw(sf::Drawable& draw)
{
	m_window.draw(draw);
}

void Game::setWindowSize(sf::Vector2f size)
{
	m_window.setSize((sf::Vector2u)size);
}
