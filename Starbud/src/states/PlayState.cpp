#include "PlayState.h"

void PlayState::update(const float dt)
{
	level->update(dt);
}

void PlayState::draw(const float dt)
{
	game->m_window.setView(this->view);

	level->draw(dt);

	if (level->gameover)
	{
		game->draw(gameoverBG);
		game->draw(gameoverText);
		gameoverMenu->draw(dt);
	}
}

void PlayState::handleInput(sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		switch (event.key.code)
		{
		case sf::Keyboard::Up:
			gameoverMenu->selectUp();
			break;
		case sf::Keyboard::Down:
			gameoverMenu->selectDown();
			break;
		case sf::Keyboard::Return:
			if (gameoverMenu->selected == 0) level = new Level(game);
			else if (gameoverMenu->selected == 1) game->pushState(new MenuState(game));
			else if (gameoverMenu->selected == 2) game->m_window.close();
		}
		break;
	}
}

PlayState::PlayState(Game* game)
{
	this->game = game;
	sf::Vector2f size = sf::Vector2f(APP_WIDTH, APP_HEIGHT);
	view.setSize(size);
	size *= 0.5f;
	view.setCenter(size);
	view.setViewport(sf::FloatRect(0, 0, 1, 1));

	level = new Level(game);
	
	gameoverBG.setFillColor(sf::Color(0, 0, 0, 200));
	gameoverBG.setSize(sf::Vector2f(APP_WIDTH, APP_HEIGHT));
	SmartText::createText(gameoverText, "Gameover", 48, "pixel", sf::Color(255, 0, 0, 255));
	gameoverText.setPosition(sf::Vector2f((APP_WIDTH - gameoverText.getLocalBounds().width) / 2, 100));
	SmartText::createText(playText, "Play Again", 32, "roses");
	playText.setPosition(sf::Vector2f((APP_WIDTH - playText.getLocalBounds().width) / 2, 200));
	SmartText::createText(menuText, "Menu", 32, "roses");
	menuText.setPosition(sf::Vector2f((APP_WIDTH - menuText.getLocalBounds().width) / 2, 250));
	SmartText::createText(exitText, "Exit", 32, "roses");
	exitText.setPosition(sf::Vector2f((APP_WIDTH - exitText.getLocalBounds().width) / 2, 300));

	gameoverMenu = new TextMenu(game, sf::Color(255, 255, 255, 255), sf::Color(255, 0, 0, 255));
	gameoverMenu->addItem(playText);
	gameoverMenu->addItem(menuText);
	gameoverMenu->addItem(exitText);

}