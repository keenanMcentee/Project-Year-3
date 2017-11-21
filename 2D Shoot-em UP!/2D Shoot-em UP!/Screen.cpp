#include "Screen.h"

/// <summary>
/// screen constructor
/// creates a screen with a render window
/// </summary>
/// <param name="window"></param>
Screen::Screen(sf::RenderWindow *window)
{
	gui.setTarget(*window);
	windowPtr = window;
}

/// <summary>
/// Sets the current gamestate to the passed gamestate
/// </summary>
/// <param name="state"></param>
void Screen::GoToScreen(GameState state)
{
	*currentState = state;
}
