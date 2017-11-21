#pragma once
#include "Screen.h"
class MainMenu : public Screen
{
public:
public:
	MainMenu(sf::RenderWindow *window);
	void Initialise(GameState *state);
	void Update();
	static sf::RenderWindow* m_window;
	void Draw(sf::RenderWindow *window);
private:
	
};

