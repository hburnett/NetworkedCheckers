#include "Game.h"
#include <iostream>

int main(int argc, char** argv)
{
	Game *newGame = new Game(900, 900, "Swing Jumper", false);

	newGame->RunGame();
	delete newGame;

	return 0;
}