#pragma once
#include "Screen.h"
class Help : public Screen
{
public:
	Help(sf::RenderWindow *window);
	void Initialise(GameState *state);
	void Update(sf::Time dt);
	void Draw(sf::RenderWindow *window);
private:
	sf::Texture menuBox;
	sf::Sprite m_menuBox;
};

