#include "Game.h"
#include "states\MenuState.h"

int main() 
{
	Game game;

	game.pushState(new MenuState(&game));
	game.gameLoop();

	return 0;
}