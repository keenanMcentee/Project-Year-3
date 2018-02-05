#pragma once
#include "Screen.h"
class Credits : public Screen
{
public:
	Credits(sf::RenderWindow *window);
	void Initialise(GameState *state);
	void Update();
	void Draw(sf::RenderWindow *window);
private:

};

