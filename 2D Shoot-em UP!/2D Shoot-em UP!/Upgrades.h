#pragma once
#include "Screen.h"
#include"playerStats.h"
class Upgrades : public Screen
{
public:
	PlayerStats* stats;
	Upgrades(sf::RenderWindow *window);
	void Initialise(GameState *state, PlayerStats* _stats);
	void Draw(sf::RenderWindow *window, sf::Time dt);
	void initbuttons();
	void initSprites();
	void initLabels();
	void buy();
	void reset();
	void setTexture();
private:
	int tempLWingLevel;
	int tempRWingLevel;
	int tempBodyLevel;
	sf::Texture menuBox;
	sf::Sprite m_menuBox1;
	sf::Sprite m_menuBox2;
	sf::Sprite m_menuBox3;
};
