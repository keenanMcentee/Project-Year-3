#pragma once
#include "Screen.h"
class Upgrades : public Screen
{
public:
	Upgrades(sf::RenderWindow *window);
	void Initialise(GameState *state);
	void Draw(sf::RenderWindow *window);
	void buy(int shipLv);

	int m_lv1ShipCost = 500;
	int m_lv2ShipCost = 1000;
	int m_lv3ShipCost = 2000;
	int m_lv4ShipCost = 4000;
	int m_lv5ShipCost = 10000;

	sf::Sprite m_lv1ShipSprite;
	sf::Sprite lv2ShipSprite;
	sf::Sprite lv3ShipSprite;
	sf::Sprite lv4ShipSprite;
	sf::Sprite lv5ShipSprite;
	sf::Texture m_lv1ShipTexture;
	sf::Texture m_lv2ShipTexture;
	sf::Texture m_lv3ShipTexture;
	sf::Texture m_lv4ShipTexture;
	sf::Texture m_lv5ShipTexture;
};

