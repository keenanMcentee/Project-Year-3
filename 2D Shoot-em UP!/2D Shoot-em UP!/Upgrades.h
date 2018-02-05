#pragma once
#include "Screen.h"
#include "Player.h"
class Upgrades : public Screen
{
public:
	Player *m_player;
	Upgrades(sf::RenderWindow *window);
	void Initialise(GameState *state, Player *player);
	void Draw(sf::RenderWindow *window);
	void buy(int shipLv);
	void initbuttons();
	void initSprites();
	void initLabels();

	int m_lv1ShipCost = 500;
	int m_lv2ShipCost = 1000;
	int m_lv3ShipCost = 2000;
	int m_lv4ShipCost = 4000;
	int m_lv5ShipCost = 10000;

	sf::Sprite m_lv1ShipSprite;
	sf::Sprite m_lv2ShipSprite;
	sf::Sprite m_lv3ShipSprite;
	sf::Sprite m_lv4ShipSprite;
	sf::Sprite m_lv5ShipSprite;
	sf::Texture m_lv1ShipTexture;
	sf::Texture m_lv2ShipTexture;
	sf::Texture m_lv3ShipTexture;
	sf::Texture m_lv4ShipTexture;
	sf::Texture m_lv5ShipTexture;
};
