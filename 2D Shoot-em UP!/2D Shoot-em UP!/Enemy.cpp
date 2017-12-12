#include "Enemy.h"
Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::Initialise()
{
	m_texture.loadFromFile("ASSETS/robotSprite.png");
	
	srand(time(NULL));

	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
	m_position = sf::Vector2f(rand() % 700 + 50, rand() % 700 + 50);

	m_direction = "Up";
	m_sprite.scale(3, 3);
	m_sprite.setPosition(m_position);
	m_speed = 1;
}

void Enemy::Update(sf::Time dt, sf::Vector2f playerPos)
{
	HandleMovement(playerPos);
	m_sprite.setPosition(m_position);
}

void Enemy::HandleMovement(sf::Vector2f playerPos)
{
	if (m_position.x < playerPos.x)
	{
		m_position.x += m_speed;
		m_direction = "Right";
	}

	else if (m_position.x > playerPos.x)
	{
		m_position.x -= m_speed;
		m_direction = "Left";
	}

	else if (m_position.y < playerPos.y)
	{
		m_position.y += m_speed;
		m_direction = "Down";
	}

	else if (m_position.y > playerPos.y)
	{
		m_position.y -= m_speed;
		m_direction = "Up";
	}

	if (m_direction == "Up")
	{
		m_sprite.setRotation(0);
	}

	else if (m_direction == "Right")
	{
		m_sprite.setRotation(90);
	}

	else if (m_direction == "Down")
	{
		m_sprite.setRotation(180);
	}

	else if (m_direction == "Left")
	{
		m_sprite.setRotation(270);
	}

}

void Enemy::Draw(sf::RenderWindow *window)
{
	window->draw(m_sprite);
}

tgui::FloatRect Enemy::getRect()
{	
	sf::FloatRect boundingBox = m_sprite.getGlobalBounds();
	return tgui::FloatRect(boundingBox.left, boundingBox.top, boundingBox.width, boundingBox.height);
}