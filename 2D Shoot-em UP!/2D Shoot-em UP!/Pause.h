#pragma once
#include "Screen.h"
class Pause : public Screen
{
public:
public:
	Pause(sf::RenderWindow *window);
	void Initialise(GameState *state, bool* fromPause);
	void Update();
	void Draw(sf::RenderWindow *window);
	
private:
	sf::Texture menuBox;
	sf::Sprite m_menuBox;
};

