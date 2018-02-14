#include "Enemy.h"
Enemy::Enemy()
{
}


Enemy::~Enemy()
{
	m_texture.~Texture();
}

void Enemy::Initialise(int type, sf::RenderWindow *window, sf::Vector2f spawnPos, sf::Vector2f speed, bool circleType)
{
	m_ramType = circleType;

	if (m_ramType)
	{
		m_texture.loadFromFile("ASSETS/enemyBallThingie.png");
		m_sprite.setTexture(m_texture);
		m_sprite.setScale(0.02f, 0.02f);
	}
	else if (!m_ramType)
	{
		m_texture.loadFromFile("ASSETS/BulletShootingShip.png");
		m_sprite.setTexture(m_texture);
		m_sprite.setScale(0.03f, 0.03f);
	}
	m_window = window;

	m_position = sf::Vector2f(spawnPos.x, spawnPos.y);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
	m_sprite.setPosition(m_position);

	m_type = type;

	rotator = 0;
	
	m_speed = speed;

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
	/*std::cout << m_position.x << std::endl;
	std::cout << m_position.y << std::endl;*/
	//Height of curve		width of curve		position on screen.
	switch (m_type)
	{
	case 0: //Large_SinWave_Type
		m_position.x -= m_speed.x;
		m_position.y = 100 * sin(m_position.x / 100) + 400;
		break;

		default:
			break;
	
		
		
	}
	if (m_type == Small_SinWave_Type)
	{
		m_position.x += m_speed.x;
		m_position.y = 100 * sin(m_position.x / 10) + 300;

		if (m_position.x > m_window->getSize().x)
		{
			alive = false;
		}
	}
	else if (m_type == Go_To_Center_Type)
	{
		if (m_position.y < m_window->getSize().y / 2)
		{
			m_position.y += m_speed.y;
		}
	}
	else if (m_type == Go_Left_To_Right_Type)
	{
		if (m_position.x < m_window->getSize().x + 100)
		{
			m_position.x += m_speed.x;
		}

		if (m_position.x > m_window->getSize().x)
		{
			alive = false;
		}

	}
	else if (m_type == Go_Right_To_Left_Type)
	{
		if (m_position.x > 100)
		{
			m_position.x -= m_speed.x;
		}

		if (m_position.x + m_texture.getSize().x < 0)
		{
			alive = false;
		}
	}
	// should work but doesnt
	else if (m_type == Digonal_Moving_Type)
	{
		m_position += m_speed;
		
		if (m_position.x <= 200)
		{
			m_speed.x = 2;
		}

		if (m_position.x + m_sprite.getGlobalBounds().width >= m_window->getSize().x)
		{
			m_speed.x = -2;
		}

		if (m_position.y <= 0)
		{
			m_speed.y = 2;
		}

		if (m_position.y >= 500)
		{
			m_speed.y = -2;
		}
	}
	else if (m_type == Tracker_Type)
	{
		if (m_position.x < playerPos.x)
		{
			m_position.x += m_speed.x;
		}

		else if (m_position.x > playerPos.x)
		{
			m_position.x -= m_speed.x;
		}

	}
	if (m_ramType)
	{
		m_sprite.setRotation(rotator);
	}
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