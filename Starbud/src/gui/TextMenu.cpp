#include "TextMenu.h"

void TextMenu::addItem(sf::Text& text)
{
	textItems.push_back(text);
}

void TextMenu::selectDown()
{
	selected++;
	if (selected >= textItems.size()) 
	{
		selected = textItems.size() - 1;
		return;
	}
	select.play();
}

void TextMenu::selectUp()
{
	selected--;
	if (selected < 0) 
	{
		selected = 0;
		return;
	}
	select.play();
}

void TextMenu::handleInput(sf::Event& event)
{
	switch (event.key.code)
	{
	case sf::Keyboard::Up:
		selectUp();
		break;
	case sf::Keyboard::Down:
		selectDown();
		break;
	case sf::Keyboard::Return:
		select.play();
		action = true;
		break;
	}
}

void TextMenu::draw(const float dt)
{
	for (int i = 0; i < textItems.size(); i++)
	{
		if (selected == i) textItems[i].setFillColor(on);
		else textItems[i].setFillColor(off);
		game->draw(textItems[i]);
	}
}

TextMenu::TextMenu(Game* game, sf::Color& off, sf::Color& on)
{
	this->game = game;

	this->on = on;
	this->off = off;
	select = SoundManager::getSoundRef("select");

	selected = 0;
	action = false;
}