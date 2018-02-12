#include "Enemy.h"
Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::Initialise(int type, sf::RenderWindow *window, sf::Vector2f spawnPos)
{
	m_texture.loadFromFile("ASSETS/enemyBallThingie.png");

	m_window = window;

	m_position = sf::Vector2f(spawnPos.x, spawnPos.y);

	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
	m_sprite.setScale(0.01f, 0.01f);
	m_sprite.scale(3, 3);
	m_sprite.setPosition(m_position);

	m_type = type;

	rotator = 0;
	
	m_speed = 0.5;

	alive = true;
}

void Enemy::Update(sf::Time dt, sf::Vector2f playerPos)
{
	if (alive)
	{
		HandleMovement(playerPos);
		m_sprite.setPosition(m_position);
	}
	rotator += 1;
}

void Enemy::HandleMovement(sf::Vector2f playerPos)
{
	std::cout << m_position.x << std::endl;
	std::cout << m_position.y << std::endl;
	//Height of curve		width of curve		position on screen.
	if (m_type == Large_SinWave_Type)
	{
		m_position.x += m_speed;
		m_position.y = 100 * sin(m_position.x / 100) + 400;
	}
	else if (m_type == Small_SinWave_Type)
	{
		m_position.x += m_speed;
		m_position.y = 100 * sin(m_position.x / 10) + 300;
	}
	else if (m_type == Go_To_Center_Type)
	{
		if (m_position.y < m_window->getSize().y / 2)
		{
			m_position.y += 2;
		}
	}
	else if (m_type == Go_Left_To_Right_Type)
	{
		if (m_position.x < m_window->getSize().x + 100)
		{
			m_position.x += 2;
		}
	}
	

	m_sprite.setRotation(rotator);
}

void Enemy::Draw()
{
	if (alive)
		m_window->draw(m_sprite);
}

tgui::FloatRect Enemy::getRect()
{
	if (alive)
	{
		sf::FloatRect boundingBox = m_sprite.getGlobalBounds();
		return tgui::FloatRect(boundingBox.left, boundingBox.top, boundingBox.width, boundingBox.height);
	}
	else
	{
		return tgui::FloatRect(0, 0, 0, 0);
	}
}