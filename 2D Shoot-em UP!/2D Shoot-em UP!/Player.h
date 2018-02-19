#ifndef PLAYER
#define PLAYER


#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <Thor\Animations.hpp>
#include <Thor\Particles.hpp>
#include <math.h>
#include "uiHelper.h"

#include "Projectile.h"
#include "uiHelper.h"

#include "Enemy.h"

#include "playerStats.h"
#include <math.h>
class Player
{
public:
	PlayerStats playerStats;
	sf::Texture m_texture;
	sf::Texture m_bulletTexture;
	sf::Texture m_flashAnimation;
	sf::Texture blankTexture;
	thor::Animator<sf::Sprite, std::string> animator;
	thor::FrameAnimation gunFlashAnimation;

	sf::Sprite m_sprite;
	sf::Sprite m_gunFlash;
	sf::Sprite healthBar;
	sf::Shader healthBarShader;
	sf::Sprite healthBarBackground;
	sf::Vector2f m_position;
	sf::Vector2f m_previousPos;
	sf::Sprite healthBarOverlay;
	sf::Texture healthBarOverlayTexture;

	Player();

	sf::RenderWindow *m_window;

	void Initialise(sf::RenderWindow *window);
	void Update(sf::Time dt, sf::Keyboard &keyboard, sf::View *view, sf::Sound *shootingSound);
	void Draw();
	void HandleMovement(sf::Keyboard &keyboard, sf::View *view, sf::Sound *shootingSound);
	void bulletEnemyCollision(Projectile b, Enemy *enemy);
	void lookAtMouse(sf::RenderWindow &win);
	void CheckCollision(tgui::FloatRect &tile);
	void setTexture();
	void reset();

	float m_speed;
	float rotation;
	float m_fireRate;
	float m_timeSinceLastShot;
	float ToRadians(float x);

	int m_health;
	int m_credits = 0;



	bool prevLeftClick;
	std::vector<Projectile*> bullets;
	
	sf::SoundBuffer buffer;
	tgui::FloatRect getRect();
	float shaderTimer;
	float particleTime;
	thor::ParticleSystem system;
	thor::UniversalEmitter emitter;
	sf::Texture flameTexture;
	sf::Sprite flameSprite;
};
#endif // !PLAYER