#include <SFML\Graphics.hpp>
#include <Thor\Animations.hpp>
#include <math.h>
#include "Projectile.h"
#include <Box2D\Box2D.h>
#include "bodyHelper.h"
class Enemy
{
public:
	Enemy();
	~Enemy();
	b2Body* m_body;
	sf::Texture m_texture;
	sf::Texture m_bulletTexture;
	sf::Texture m_flashAnimation;
	thor::Animator<sf::Sprite, std::string> animator;
	sf::Sprite m_sprite;
	sf::Sprite m_gunFlash;
	sf::Vector2f m_position;

	void Initialise(b2World* world);
	void Update(sf::Time dt, sf::Keyboard &keyboard, sf::View *view);
	void Draw(sf::RenderWindow *window);
	void HandleMovement(sf::Keyboard &keyboard, sf::View *view);
	float m_speed;
	float rotation;
	std::vector<Projectile> bullets;
	thor::FrameAnimation gunFlashAnimation;
	float m_fireRate;
	float m_timeSinceLastShot;
};

