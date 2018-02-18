#include "Enemy.h"
Enemy::Enemy()
{
}

Enemy::~Enemy()
{

}

void Enemy::Initialise(int type, bool mineType, sf::RenderWindow *window, sf::Vector2f spawnPos, sf::Vector2f speed, sf::Sprite sprite, int health, int damage, int creditsValue)
{
	m_mineType = mineType;
	m_type = type;

	if (m_type != 7)
	{
		m_sprite = sprite;
	}

	else
	{
		m_texture.loadFromFile("ASSETS/motherShip.png");
		m_sprite.setTexture(m_texture);

		m_turretOneTexture.loadFromFile("ASSETS/motherShipTurret.png");

		m_turretOneSprite.setTexture(m_turretOneTexture);
		m_turretOneSprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
		m_turretOnePosition = sf::Vector2f(200, 200);
		m_turretOneSprite.setPosition(m_position);

	/*	m_turretTwoSprite.setTexture(m_turretOneTexture);
		m_turretTwoSprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
		m_turretTwoSprite.setPosition(m_position);*/

		/*m_turretThreeSprite.setTexture(m_turretOneTexture);
		m_turretThreeSprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
		m_turretThreeSprite.setPosition(m_position);*/
	}
	
	m_health = health;
	m_damage = damage;
	m_creditsValue = creditsValue;
	m_fireRate = 1.5 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (3.0 - 1.5)));

	m_bulletTexture.loadFromFile("ASSETS/laserSprite.png");

	m_window = window;

	m_initPos = sf::Vector2f(spawnPos.x, spawnPos.y);
	m_position = m_initPos;
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
	m_sprite.setPosition(m_position);

	rotator = 0;
	
	m_speed = speed;

	alive = true;
}

void Enemy::Update(sf::Time dt, sf::Vector2f playerPos)
{
	if (m_health <= 0)
	{
		alive = false;
	}
	
	if (alive)
	{
		HandleMovement(playerPos);
		m_sprite.setPosition(m_position);
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->update();
		if (bullets[i]->getRect().getPosition().x + m_sprite.getGlobalBounds().width > m_window->getSize().x || bullets[i]->getRect().getPosition().x < 0 ||
			bullets[i]->getRect().getPosition().y > m_window->getSize().y || bullets[i]->getRect().getPosition().y < 0)
		{
			bullets[i]->~Projectile();
			bullets[i] = nullptr;
			bullets.erase(bullets.begin() + i);
			i--;
		}
	}

	rotator += 1;

	m_timeSinceLastShot += dt.asSeconds();
}

void Enemy::HandleMovement(sf::Vector2f playerPos)
{
	//Height of curve		width of curve		position on screen.
	switch (m_type)
	{
	case 0: //Large_SinWave_Type
		m_position.x -= m_speed.x;
		m_position.y = 100 * sin(m_position.x / 100) + 400;
		if (m_position.x < 0)
		{
			alive = false;
		}
		break;
	case 1: //Small_SinWave_Type
		m_position.x += m_speed.x;
		m_position.y = 150 * sin(m_position.x / 20) + 300;

		if (m_position.x + m_sprite.getGlobalBounds().width > m_window->getSize().x)
		{
			alive = false;
		}
		break;
	case 2: //Left_To_Right_Type
		if (m_position.x < m_window->getSize().x + 100)
		{
			m_position.x += m_speed.x;
		}
		if (m_position.x > m_window->getSize().x)
		{
			alive = false;
		}
		break;
	case 3: //Right_To_Left_Type
		if (m_position.x > -100)
		{
			m_position.x -= m_speed.x;
		}

		if (m_position.x + m_sprite.getGlobalBounds().width < 0)
		{
			alive = false;
		}
		break;
	case 4: //Tracker_Type
		if (m_position.y < 100)
		{
			m_position.y += m_speed.y;
		}
		
		if (m_position.x < playerPos.x)
		{
			m_position.x += m_speed.x;
		}
		else if (m_position.x > playerPos.x)
		{
			m_position.x -= m_speed.x;
		}
		break;
	case 5: //Diagonal_Moving_Type
		m_position += m_speed;
		if (m_position.x <= 0)
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
		if (m_position.y >= m_window->getSize().y)
		{
			m_speed.y = -2;
		}
		break;
	case 6: //Follower_Type
		m_position += m_speed;
		if (m_position.x <= playerPos.x)
		{
			m_speed.x = 2;
		}
		if (m_position.x >= playerPos.x)
		{
			m_speed.x = -2;
		}
		if (m_position.y <= playerPos.y)
		{
			m_speed.y = 2;
		}
		if (m_position.y >= playerPos.y)
		{
			m_speed.y = -2;
		}
		break;
	case 7: //Go_To_Center
		if (m_position.y < 150)
		{
			m_position.y += m_speed.y;
		}
		default:
			break;
	}

	if (!m_mineType && m_timeSinceLastShot > m_fireRate && alive == true)
	{
		m_timeSinceLastShot = 0;
		Projectile *bullet = new Projectile(m_position, m_sprite.getRotation() + 90, 2, 15, 1500, &m_bulletTexture, m_window);
		bullets.push_back(bullet);
	}

	if (m_mineType)
	{
		m_sprite.setRotation(rotator);
	}
}

void Enemy::Draw()
{
	if (alive)
	{
		m_window->draw(m_sprite);

		if (m_type == 7)
		{
			m_window->draw(m_turretOneSprite);
		}
	}

	for (auto &b : bullets)
	{
		b->draw();
	}
}

void Enemy::Reset()
{
	m_position = m_initPos;
	alive = true;
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