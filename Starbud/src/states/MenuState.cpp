#include "MenuState.h"

#include "PlayState.h"

void MenuState::update(const float dt)
{
	switch (page)
	{
	case 0:
		if (menu->action)
		{
			switch (menu->selected)
			{
			case 0:
				game->pushState(new PlayState(game));
				break;
			case 1:
				page = 1;
				menu->action = false;
				break;
			case 2:
				game->m_window.close();
				break;
			}
		}

		break;
	case 1:
		if (aboutMenu->action)
		{
			switch (aboutMenu->selected)
			{
			case 0:
				page = 0;
				aboutMenu->action = false;
				break;
			}
		}
		break;
	}
	
}

void MenuState::draw(const float dt)
{
	game->m_window.setView(this->view);

	switch (page)
	{
	case 0:
		game->draw(titleText);
		game->draw(baseText);
		menu->draw(dt);

		break;
	case 1:
		game->draw(aboutTitle);
		game->draw(about1);
		game->draw(about2);
		aboutMenu->draw(dt);
		break;
	}
	
}

void MenuState::handleInput(sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		switch (page)
		{
		case 0:
			menu->handleInput(event);
			break;
		case 1:
			aboutMenu->handleInput(event);
			break;
		}
	}
}

MenuState::MenuState(Game* game)
{
	this->game = game;
	sf::Vector2f size = sf::Vector2f(APP_WIDTH, APP_HEIGHT);
	view.setSize(size);
	size *= 0.5f;
	view.setCenter(size);
	view.setViewport(sf::FloatRect(0, 0, 1, 1));

	page = 0;

	//Main Menu
	SmartText::createText(titleText, APP_TITLE, 56, "pixel", sf::Color(200, 0, 255, 255));
	titleText.setPosition(sf::Vector2f((APP_WIDTH-titleText.getLocalBounds().width)/2, 100));
	SmartText::createText(playText, "PLAY GAME", 32, "roses");
	playText.setPosition(sf::Vector2f((APP_WIDTH - playText.getLocalBounds().width) / 2, 280));
	SmartText::createText(aboutText, "ABOUT", 32, "roses");
	aboutText.setPosition(sf::Vector2f((APP_WIDTH - aboutText.getLocalBounds().width) / 2, 330));
	SmartText::createText(exitText, "EXIT", 32, "roses");
	exitText.setPosition(sf::Vector2f((APP_WIDTH - exitText.getLocalBounds().width) / 2, 380));
	SmartText::createText(baseText, APP_VERSION, 16, "roses");
	baseText.setPosition(sf::Vector2f((APP_WIDTH - baseText.getLocalBounds().width) / 2, 580));

	menu = new TextMenu(game, sf::Color(255, 255, 255, 255), sf::Color(0, 255, 255, 255));
	menu->addItem(playText);
	menu->addItem(aboutText);
	menu->addItem(exitText);

	//About
	SmartText::createText(aboutTitle, "About", 48, "pixel");
	aboutTitle.setPosition(sf::Vector2f((APP_WIDTH - aboutTitle.getLocalBounds().width) / 2, 50));

	SmartText::createText(about1, "Controls: Left and Right Arrows Control Paddle", 16, "roses");
	about1.setPosition(sf::Vector2f((APP_WIDTH - about1.getLocalBounds().width) / 2, 150));
	SmartText::createText(about2, "Created by Justin Symmank", 16, "roses");
	about2.setPosition(sf::Vector2f((APP_WIDTH - about2.getLocalBounds().width) / 2, 200));

	SmartText::createText(returnText, "RETURN", 32, "roses");
	returnText.setPosition(sf::Vector2f((APP_WIDTH - returnText.getLocalBounds().width) / 2, 550));

	aboutMenu = new TextMenu(game, sf::Color(255, 255, 255, 255), sf::Color(0, 255, 255, 255));
	aboutMenu->addItem(returnText);
}
