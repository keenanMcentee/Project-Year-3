#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <Thor\Animations.hpp>
#include <math.h>
#include "Projectile.h"
#include "uiHelper.h"
class Player
{
public:
	sf::Texture m_texture;
	sf::Texture m_bulletTexture;
	sf::Texture m_flashAnimation;
	thor::Animator<sf::Sprite, std::string> animator;
	sf::Sprite m_sprite;
	sf::Sprite m_gunFlash;
	sf::Vector2f m_position;
	sf::Vector2f m_previousPos;
	Player();
	void Initialise();
	void Update(sf::Time dt, sf::Keyboard &keyboard, sf::View *view);
	void Draw(sf::RenderWindow *window);
	void HandleMovement(sf::Keyboard &keyboard, sf::View *view);
	float m_speed;
	void lookAtMouse(sf::RenderWindow &win);
	float rotation;
	bool prevLeftClick;
	std::vector<Projectile> bullets;
	thor::FrameAnimation gunFlashAnimation;
	float m_fireRate;
	float m_timeSinceLastShot;
	void CheckCollision(tgui::FloatRect &tile);

	sf::SoundBuffer buffer;
};

