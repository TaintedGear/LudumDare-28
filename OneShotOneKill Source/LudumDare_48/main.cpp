#include <SDL.h>

#include "Game.h"

int main(int argc, char* args[])
{
	Game game;

	// Initialise the dependancy libs for the game
	if(!game.Initialise())
	{
		return 0;
	}

	// Runs the game loop
	game.Run();

	// Deallocate all games assets and libs
	game.Shutdown();

	return 0;
}