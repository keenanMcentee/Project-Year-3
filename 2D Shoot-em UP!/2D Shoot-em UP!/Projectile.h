#include <SFML\Graphics.hpp>
class Projectile
{
public:
	Projectile(sf::Vector2f position, float rotation, float speed, float damage, float distance, sf::Texture *texture);
	void update();
	void draw(sf::RenderWindow *window);
	bool isAlive();
private:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_startPos;
	float m_damage;
	float m_maxDist;
	bool m_alive;

	sf::Sprite m_sprite;
};

