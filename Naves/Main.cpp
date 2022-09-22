#include "Game.h"
#undef main

int main() 
{
	Game game = Game::getInstance();
	game.start();
	return 0;
}