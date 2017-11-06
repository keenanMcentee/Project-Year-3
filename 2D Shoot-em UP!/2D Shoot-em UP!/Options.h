#pragma once
#include "Screen.h"
class Options : public Screen
{
public:
public:
	Options(sf::RenderWindow *window);
	void Initialise(GameState *state);
	void Update();
	void Draw(sf::RenderWindow *window);
private:

};

