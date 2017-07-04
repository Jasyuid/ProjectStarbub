#include "MenuState.h"

#include "PlayState.h"

void MenuState::update(const float dt)
{

}

void MenuState::draw(const float dt)
{
	game->m_window.setView(this->view);

	game->draw(titleText);
	game->draw(baseText);

	menu->draw(dt);
}

void MenuState::handleInput(sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		switch (event.key.code)
		{
		case sf::Keyboard::Up:
			menu->selectUp();
			break;
		case sf::Keyboard::Down:
			menu->selectDown();
			break;
		case sf::Keyboard::Return:
			if(menu->selected == 0) game->pushState(new PlayState(game));
			else if (menu->selected == 1) game->m_window.close();
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

	SmartText::createText(titleText, APP_TITLE, 56, "pixel", sf::Color(0, 255, 255, 255));
	titleText.setPosition(sf::Vector2f((APP_WIDTH-titleText.getLocalBounds().width)/2, 100));
	SmartText::createText(playText, "Play Game", 32, "roses");
	playText.setPosition(sf::Vector2f((APP_WIDTH - playText.getLocalBounds().width) / 2, 300));
	SmartText::createText(exitText, "Exit", 32, "roses");
	exitText.setPosition(sf::Vector2f((APP_WIDTH - exitText.getLocalBounds().width) / 2, 370));
	SmartText::createText(baseText, APP_VERSION, 16, "roses");
	baseText.setPosition(sf::Vector2f((APP_WIDTH - baseText.getLocalBounds().width) / 2, 580));

	menu = new TextMenu(game, sf::Color(255, 255, 255, 255), sf::Color(255, 0, 0, 255));
	menu->addItem(playText);
	menu->addItem(exitText);
}
