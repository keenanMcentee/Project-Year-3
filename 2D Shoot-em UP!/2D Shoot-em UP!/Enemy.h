#include <SFML\Graphics.hpp>
#include <Thor\Animations.hpp>
#include <math.h>
#include "uiHelper.h"
#include "Projectile.h"
#include <math.h>

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
	sf::Texture m_turretOneTexture;
	

	sf::Sprite m_turretOneSprite;
	sf::Sprite m_turretTwoSprite;
	sf::Sprite m_turretThreeSprite;

	sf::Sprite m_sprite;
	sf::Sprite m_gunFlash;

	thor::Animator<sf::Sprite, std::string> animator;
	thor::FrameAnimation gunFlashAnimation;

	sf::Vector2f m_position;
	sf::Vector2f m_turretOnePosition;
	sf::Vector2f m_turretTwoPosition;
	sf::Vector2f m_turretThreePosition;
	sf::Vector2f m_initPos;
	sf::Vector2f m_speed;

	sf::String m_direction;

	void Initialise(int type, bool mineType, sf::RenderWindow *window, sf::Vector2f spawnPos, sf::Sprite sprite, int health, int damage, int creditsValue);
	void Update(sf::Time dt, sf::Vector2f playerPos, float accelerator);
	void Draw();
	void Reset();
	void HandleMovement(sf::Vector2f playerPos);
	float turretLookAtPlayer(sf::Sprite turret, sf::Vector2f playerPos);

	std::vector<Projectile*> bullets;

	float m_fireRate;
	float m_timeSinceLastShot;
	float rotator;
	float rotation;

	bool alive;
	bool m_mineType;

	int m_type;
	int m_health;
	int m_turretOneHealth;
	int m_turretTwoHealth;
	int m_turretThreeHealth;
	int m_damage;
	int m_creditsValue;
	

	tgui::FloatRect getRect();

	sf::RenderWindow* m_window;

	const int LARGE_SINWAVE_TYPE = 0;
	const int SMALL_SINWAVE_TYPE = 1;
	const int GO_LEFT_TO_RIGHT_TYPE = 2;
	const int GO_RIGHT_TO_LEFT_TYPE = 3;
	const int TRACKER_TYPE = 4;
	const int DIAGONAL_MOVING_TYPE = 5;
	const int FOLLOWER_TYPE = 6;
	const int BOSS_TYPE = 7;
};

#endif