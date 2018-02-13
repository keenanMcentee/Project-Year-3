#pragma once
#include "Screen.h"
class MainMenu : public Screen
{
public:
public:
	MainMenu(sf::RenderWindow *window);
	void Initialise(GameState *state, bool* fromPause);
	void Update(sf::Time dt);
	void Draw(sf::RenderWindow *window);
	bool* m_fromPause;
	sf::Texture menuBox;
	sf::Sprite m_menuBox;
private:
	
};

