#include "Screen.h"

Screen::Screen(sf::RenderWindow *window)
{
	gui.setTarget(*window);
	windowPtr = window;
}

void Screen::GoToScreen(GameState state)
{
	*currentState = state;
}