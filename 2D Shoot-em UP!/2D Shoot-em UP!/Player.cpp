#include "Player.h"
#include <iostream>
#include "vector2.h"
Player::Player()
{
}
void Player::Initialise()
{
	m_texture.loadFromFile("ASSETS/playerSprite.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
	m_sprite.setScale(2.0f,2.0f);
	m_position = sf::Vector2f(256, 256);
	m_speed = 2;
	
}

void Player::Update(sf::Keyboard &keyboard)
{
	HandleMovement(keyboard);
	m_sprite.setPosition(m_position);
}
void Player::Draw(sf::RenderWindow *window)
{
	lookAtMouse(*window);
	window->draw(m_sprite);
}
void Player::HandleMovement(sf::Keyboard &keyboard)
{
	
	if (keyboard.isKeyPressed(keyboard.A))
	{
		m_position.x -= m_speed;
	}
	else if (keyboard.isKeyPressed(keyboard.D))
	{
		m_position.x += m_speed;
	}
	if (keyboard.isKeyPressed(keyboard.W))
	{
		m_position.y -= m_speed;
	}
	else if (keyboard.isKeyPressed(keyboard.S))
	{
		m_position.y += m_speed;
	}
	
}
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