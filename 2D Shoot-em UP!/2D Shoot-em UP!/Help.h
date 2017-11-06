#pragma once
#include "Screen.h"
class Help : public Screen
{
public:
public:
	Help(sf::RenderWindow *window);
	void Initialise(GameState *state);
	void Update();
	void Draw(sf::RenderWindow *window);
private:

};

