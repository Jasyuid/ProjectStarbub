#include "PlayState.h"

void PlayState::update(const float dt)
{
	level->update(dt);

}

void PlayState::draw(const float dt)
{
	game->m_window.setView(this->view);

	level->draw(dt);

}

void PlayState::handleInput(sf::Event& event)
{
	switch (event.type)
	{
	default:
		level->handleInput(event);
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

	level = new Level(this);

}