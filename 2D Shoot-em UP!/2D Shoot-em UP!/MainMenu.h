#pragma once
#include "Screen.h"
class MainMenu : public Screen
{
public:
public:
	MainMenu(sf::RenderWindow *window);
	void Initialise(GameState *state, bool* fromPause);
	void Update();
	static sf::RenderWindow* m_window;
	void Draw(sf::RenderWindow *window);
	bool* m_fromPause;
private:
	
};

