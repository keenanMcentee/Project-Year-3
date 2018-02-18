#include <SFML\Graphics.hpp>
#include "uiHelper.h"

#ifndef PROJECTILE
#define PROJECTILE

class Projectile
{
public:
	Projectile(sf::Vector2f position, float rotation, float speed, float damage, float distance, sf::Texture *texture, sf::RenderWindow *window);
	~Projectile();
	void update();
	void draw();
	float m_damage;
	sf::Vector2f m_position;

	sf::RenderWindow *m_window;

	tgui::FloatRect getRect();
	bool isAlive();
private:
	sf::Vector2f m_velocity;
	sf::Vector2f m_startPos;
	float m_maxDist;
	bool m_alive;
	sf::Sprite m_sprite;
};


#endif // !PROJECTILE
