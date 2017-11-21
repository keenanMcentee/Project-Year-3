#pragma once
#include "Screen.h"
class MainMenu : public Screen
{
public:
public:
	MainMenu(sf::RenderWindow *window);
	void Initialise(GameState *state);
	void Update();
	void Draw(sf::RenderWindow *window);
private:
	
};

