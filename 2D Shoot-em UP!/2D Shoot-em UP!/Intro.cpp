#include "Game.h"

/// <summary>
/// Entry point for the game.
/// </summary>
/// <returns></returns>
int main()
{
	Game game;
	srand(time(NULL));
	srand(static_cast <unsigned> (time(NULL)));
	game.Run();
}
