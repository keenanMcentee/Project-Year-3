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
	void Initialise(int type, sf::RenderWindow *window, sf::Vector2f spawnPos);
	void Update(sf::Time dt, sf::Vector2f playerPos);
	void Draw();
	void HandleMovement(sf::Vector2f playerPos);
	sf::Vector2f m_speed;
	float rotation;
	std::vector<Projectile> bullets;
	thor::FrameAnimation gunFlashAnimation;
	float m_fireRate;
	float m_timeSinceLastShot;
	tgui::FloatRect getRect();
	float rotator;
	bool alive;
	int m_type;
	sf::RenderWindow* m_window;

	const int Large_SinWave_Type = 0;
	const int Small_SinWave_Type = 1;
	const int Go_To_Center_Type = 2;
	const int Go_Left_To_Right_Type = 3;
	const int Go_Right_To_Left_Type = 4;
	const int Digonal_Moving_Type = 5;
};

#endif