#include <SFML\Graphics.hpp>
#include <Thor\Animations.hpp>
#include <math.h>
#include "uiHelper.h"
#include "Projectile.h"

#ifndef ENEMY
#define ENEMY
class Enemy
{
public:
	Enemy();
	~Enemy();
	sf::Texture m_texture;
	sf::Texture m_bulletTexture;
	sf::Texture m_flashAnimation;
	thor::Animator<sf::Sprite, std::string> animator;
	sf::Sprite m_sprite;
	sf::Sprite m_gunFlash;
	sf::Vector2f m_position;
	sf::String m_direction;
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
	tgui::FloatRect getRect();

	bool alive;
};
#endif


