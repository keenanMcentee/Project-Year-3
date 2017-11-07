#include <SFML\Graphics.hpp>
#include <math.h>
class Player
{
public:
	sf::Texture m_texture;
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
};

