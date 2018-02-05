#pragma once
#include "Screen.h"
class PostWaveMenu : public Screen
{
public:
	PostWaveMenu(sf::RenderWindow *window);
	void Initialise(GameState *state);
	void Draw(sf::RenderWindow *window);
};