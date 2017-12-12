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

	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
	//m_position = sf::Vector2f(rand() % 700 + 50, rand() % 700 + 50);

	m_position = sf::Vector2f(300, 300);
	m_sprite.scale(3, 3);
	m_sprite.setPosition(m_position);
	m_speed = 2;
}

void Enemy::Update(sf::Time dt, sf::Vector2f playerPos)
{s
	HandleMovement(playerPos);
	m_sprite.setPosition(m_position);
}

void Enemy::HandleMovement(sf::Vector2f playerPos)
{
	if (m_position.x < playerPos.x)
	{
		m_position.x++;
	}

	else if (m_position.x > playerPos.x)
	{
		m_position.x--;
	}

	else if (m_position.y < playerPos.y)
	{
		m_position.y++;
	}

	else if (m_position.y > playerPos.y)
	{
		m_position.y--;
	}
}

void Enemy::Draw(sf::RenderWindow *window)
{
	window->draw(m_sprite);
}

