#include "Screen.h"

Screen::Screen(sf::RenderWindow *window)
{
	gui.setTarget(*window);
}

void Screen::GoToScreen(GameState state)
{
	*currentState = state;
}