#include <SFML\Graphics.hpp>
#ifndef PLAYER_STATS
#define PLAYER_STATS
struct PlayerStats
{
	int l_wing_level = 0;
	int r_wing_level = 0;
	int body_level = 0;
	int l_cannon_level = 0;
	int r_cannon_level = 0;
	int healthLevel = 1;
	int maxHealth;

	const int l_wing_max_level = 8;
	const int r_wing_max_level = 6;
	const int body_max_level = 0;
	const int l_cannon_max_level = 0;
	const int r_cannon_max_level = 0;

	int cash = 0;
	std::vector < std::pair<std::string, sf::Texture*>*> ships;
	sf::Sprite m_sprite;
};

#endif // !PLAYER_STATS

