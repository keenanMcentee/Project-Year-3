#pragma once
#include "Screen.h"
#include "Play.h"
class MainMenu : public Screen
{
public:
public:
	MainMenu(sf::RenderWindow *window);
	void Initialise(GameState *state, bool* fromPause, Play* playScreen);
	void Update(sf::Time dt);
	void Draw(sf::RenderWindow *window);
	void resetButton();
	bool* m_fromPause;
	sf::Texture menuBox;
	sf::Sprite m_menuBox;
	Play *playScreenPtr;
private:
	
};

