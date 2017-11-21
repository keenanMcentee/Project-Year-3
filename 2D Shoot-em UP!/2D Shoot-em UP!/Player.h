#include <SFML\Graphics.hpp>
#include <math.h>
#include "Projectile.h"
class Player
{
public:
	sf::Texture m_texture;
	sf::Texture m_bulletTexture;
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
	Player();
	void Initialise();
	void Update(sf::Keyboard &keyboard);
	void Draw(sf::RenderWindow *window);
	void HandleMovement(sf::Keyboard &keyboard);
	float m_speed;
	void lookAtMouse(sf::RenderWindow &win);
	float rotation;
	bool prevLeftClick;
	std::vector<Projectile> bullets;
};

