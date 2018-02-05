#include "Player.h"
#include <iostream>
#include "vector2.h"
Player::Player()
{
}
/// <summary>
/// 
/// </summary>
void Player::Initialise()
{
	
	m_texture.loadFromFile("ASSETS/player/The_XTB-1.png");
	m_bulletTexture.loadFromFile("ASSETS/bullet.png");
	m_flashAnimation.loadFromFile("ASSETS/gunFire/gunFireAnimation.png");
	m_gunFlash.setTexture(m_flashAnimation);
	std::vector<sf::IntRect> rectangles;
	for (int i = 0; i < 7; i++)
	{
		sf::IntRect rect((m_flashAnimation.getSize().x / 7) * i, 0, m_flashAnimation.getSize().x / 7, m_flashAnimation.getSize().y);
		gunFlashAnimation.addFrame(0.1f, rect);
	}
	animator.addAnimation("gunFlash", gunFlashAnimation, sf::seconds(0.1f));

	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
	m_position = sf::Vector2f(300, 300);
	m_sprite.scale(0.5f, 0.5f);
	m_speed = 2;
	m_fireRate = 0.1f;

}
/// <summary>
/// 
/// </summary>
/// <param name="keyboard"></param>
void Player::Update(sf::Time dt, sf::Keyboard &keyboard, sf::View *view)
{
	std::cout << std::to_string(m_sprite.getPosition().x) << std::endl;
	std::cout << std::to_string(m_position.x) << std::endl;
	m_previousPos = m_position;
	
	animator.update(dt);
	animator.animate(m_gunFlash);
	
	HandleMovement(keyboard, view);
	for (auto &b : bullets)
	{
		b.update();
	}
	m_sprite.setPosition(m_position);

	m_timeSinceLastShot += dt.asSeconds();

}
/// <summary>
/// 
/// </summary>
/// <param name="window"></param>
void Player::Draw(sf::RenderWindow *window)
{
	std::cout << std::to_string(m_sprite.getPosition().x) << std::endl;
	m_gunFlash.setPosition(m_position + sf::Vector2f(cos(rotation * 3.14 / 180) * 9, sin(rotation * 3.14 / 180) * 12));
	m_gunFlash.setRotation(rotation);
	lookAtMouse(*window);
	for (auto &b : bullets)
	{
		b.draw(window);
	}
	window->draw(m_sprite);
	if (animator.isPlayingAnimation())
		window->draw(m_gunFlash);
	
}
/// <summary>
/// 
/// </summary>
/// <param name="keyboard"></param>
void Player::HandleMovement(sf::Keyboard &keyboard, sf::View *view)
{
	
	if (keyboard.isKeyPressed(keyboard.A))
	{
		m_position.x -= m_speed;
		view->move(sf::Vector2f(-m_speed, 0));
	}
	else if (keyboard.isKeyPressed(keyboard.D))
	{
		m_position.x += m_speed;
		view->move(sf::Vector2f(m_speed, 0));
	}
	if (keyboard.isKeyPressed(keyboard.W))
	{
		m_position.y -= m_speed;
		view->move(sf::Vector2f(0, -m_speed));
	}
	else if (keyboard.isKeyPressed(keyboard.S))
	{
		m_position.y += m_speed;
		view->move(sf::Vector2f(0, m_speed));
	}
	if (keyboard.isKeyPressed(keyboard.LShift))
	{
		m_speed = 10;
	}
	else
	{
		m_speed = 2;
	}
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_timeSinceLastShot > m_fireRate)
	{
		m_timeSinceLastShot = 0;
		Projectile bullet = Projectile(m_position, m_sprite.getRotation(), 100, 100, 400, &m_bulletTexture);
		bullets.push_back(bullet);
		animator.playAnimation("gunFlash", false);
	}
	prevLeftClick = sf::Mouse::isButtonPressed(sf::Mouse::Left);
}
/// <summary>
/// 
/// </summary>
/// <param name="win"></param>
void Player::lookAtMouse(sf::RenderWindow &win) {
	sf::Vector2f curPos = m_sprite.getPosition();
	sf::Vector2f position = win.mapPixelToCoords(sf::Mouse::getPosition(win));

	// now we have both the sprite position and the cursor
	// position lets do the calculation so our sprite will
	// face the position of the mouse
	float pi = 3.14159265;

	float dx = curPos.x - position.x;
	float dy = curPos.y - position.y;

	rotation = ((atan2(dy, dx)) * 180 / pi) + 180;

	m_sprite.setRotation(rotation);
}

tgui::FloatRect Player::getRect()
{
	sf::FloatRect boundingBox = m_sprite.getGlobalBounds();
	return tgui::FloatRect(boundingBox.left, boundingBox.top, boundingBox.width, boundingBox.height);
}

void Player::bulletEnemyCollision(Projectile b, Enemy *enemy)
{
	if (b.getRect().intersects(enemy->getRect()))
	{
		enemy->alive = false;
	}
}

void Player::CheckCollision(tgui::FloatRect &tile)
{
	if (tile.intersects(m_sprite.getGlobalBounds()))
	{
		m_position = m_previousPos;
		
	}
}