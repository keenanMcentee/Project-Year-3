#pragma once
#include "Screen.h"
class Credits : public Screen
{
public:
	Credits(sf::RenderWindow *window);
	void Initialise(GameState *state);
	void Update(sf::Time dt);
	void Draw(sf::RenderWindow *window);
private:
	sf::Texture menuBox;
	sf::Sprite m_menuBox;
};

