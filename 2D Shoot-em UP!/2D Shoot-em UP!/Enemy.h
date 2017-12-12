#include <SFML\Graphics.hpp>
#include <Thor\Animations.hpp>
#include <math.h>

#ifndef PROJECTILE
#define PROJECTILE
#include "Projectile.h"

#endif // !PROJECTILE


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

	void Initialise();
	void Update(sf::Time dt, sf::Vector2f playerPos);
	void Draw(sf::RenderWindow *window);
	void HandleMovement(sf::Vector2f playerPos);
	float m_speed;
	float rotation;
	std::vector<Projectile> bullets;
	thor::FrameAnimation gunFlashAnimation;
	float m_fireRate;
	float m_timeSinceLastShot;
};

