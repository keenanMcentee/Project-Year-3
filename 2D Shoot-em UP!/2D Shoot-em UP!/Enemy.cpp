#include "Enemy.h"
#include "vector2.h"
Enemy::Enemy()
{
}

Enemy::~Enemy()
{

}

void Enemy::Initialise(int type, bool mineType, sf::RenderWindow *window, sf::Vector2f spawnPos, sf::Sprite sprite, int health, int damage, int creditsValue)
{
	m_mineType = mineType;
	m_type = type;

	if (m_type != 7)
	{
		m_sprite = sprite;
		m_fireRate = 2.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (3.0f - 2.0f)));
	}

	else if(m_type == 7)
	{
		m_turretOneHealth = 500;
		m_turretTwoHealth = 500;
		m_turretThreeHealth = 500;

		m_texture.loadFromFile("ASSETS/motherShip.png");
		m_sprite.setTexture(m_texture);

		m_turretOneTexture.loadFromFile("ASSETS/motherShipTurret.png");

		m_turretOneSprite.setTexture(m_turretOneTexture);
		m_turretOnePosition = sf::Vector2f(195, -210);
		m_turretOneSprite.setPosition(m_turretOnePosition);
		m_turretOneSprite.setScale(sf::Vector2f(0.2f, 0.2f));
		m_turretOneSprite.setOrigin(m_turretOneSprite.getLocalBounds().width / 2, m_turretOneSprite.getLocalBounds().height / 2);

		m_turretTwoSprite.setTexture(m_turretOneTexture);
		m_turretTwoPosition = sf::Vector2f(500, -210);
		m_turretTwoSprite.setPosition(m_turretTwoPosition);
		m_turretTwoSprite.setScale(sf::Vector2f(0.2f, 0.2f));
		m_turretTwoSprite.setOrigin(m_turretTwoSprite.getLocalBounds().width / 2, m_turretTwoSprite.getLocalBounds().height / 2);

		m_turretThreeSprite.setTexture(m_turretOneTexture);
		m_turretThreePosition = sf::Vector2f(355, -210);
		m_turretThreeSprite.setPosition(m_turretThreePosition);
		m_turretThreeSprite.setScale(sf::Vector2f(0.2f, 0.2f));
		m_turretThreeSprite.setOrigin(m_turretThreeSprite.getLocalBounds().width / 2, m_turretThreeSprite.getLocalBounds().height / 2);

		m_fireRate = 0.5f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f - 0.5f)));
	}

	m_health = health;
	m_damage = damage;
	m_creditsValue = creditsValue;

	m_bulletTexture.loadFromFile("ASSETS/laserSprite.png");

	m_window = window;

	m_initPos = sf::Vector2f(spawnPos.x, spawnPos.y);
	m_position = m_initPos;
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
	m_sprite.setPosition(m_position);

	rotator = 1;
	
	m_speed = sf::Vector2f(1.0f,1.0f);

	alive = true;
}

void Enemy::Update(sf::Time dt, sf::Vector2f playerPos, float accelerator, sf::Sound *shootingSound)
{
	if (m_health <= 0)
	{
		alive = false;
	}
	
	if (alive)
	{
		HandleMovement(playerPos,shootingSound);
		m_sprite.setPosition(m_position);
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->update();
		if (bullets[i]->getRect().getPosition().x + bullets[i]->getRect().width > m_window->getSize().x + 100 || bullets[i]->getRect().getPosition().x < -60 ||
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

	m_speed = sf::Vector2f(1 * accelerator, 1 * accelerator);
	
}

void Enemy::Draw()
{
	if (alive)
	{
		m_window->draw(m_sprite);

		if (m_type == 7)
		{
			if (m_turretOneHealth > 0)
			{
				m_window->draw(m_turretOneSprite);
			}
			if (m_turretTwoHealth > 0)
			{
				m_window->draw(m_turretTwoSprite);
			}
			if (m_turretThreeHealth > 0)
			{
				m_window->draw(m_turretThreeSprite);
			}
		}
	}

	for (auto &b : bullets)
	{
		b->draw();
	}
}

void Enemy::HandleMovement(sf::Vector2f playerPos, sf::Sound *shootingSound)
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

		if (m_position.x + m_sprite.getGlobalBounds().width > m_window->getSize().x + 100)
		{
			alive = false;
		}
		break;
	case 2: //Left_To_Right_Type
		if (m_position.x < m_window->getSize().x + 100)
		{
			m_position.x += m_speed.x;
		}
		if (m_position.x > m_window->getSize().x + 100)
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
			m_speed.x *-1;
		}
		if (m_position.x + m_sprite.getGlobalBounds().width >= m_window->getSize().x)
		{
			m_speed.x *-1;
		}
		if (m_position.y <= 0)
		{
			m_speed.y * -1;
		}
		if (m_position.y >= m_window->getSize().y)
		{
			m_speed.y * -1;
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
		m_turretOneSprite.setPosition(m_turretOnePosition);
		m_turretTwoSprite.setPosition(m_turretTwoPosition);
		m_turretThreeSprite.setPosition(m_turretThreePosition);

		if (m_position.y < 150)
		{
			m_position.y += m_speed.y;
			m_turretOnePosition.y += m_speed.y;
			m_turretTwoPosition.y += m_speed.y;
			m_turretThreePosition.y += m_speed.y;
		}

		if (m_position.y >= 150)
		{
			m_turretOneSprite.setRotation(turretLookAtPlayer(m_turretOneSprite, playerPos));
			m_turretTwoSprite.setRotation(turretLookAtPlayer(m_turretTwoSprite, playerPos));
			m_turretThreeSprite.setRotation(turretLookAtPlayer(m_turretThreeSprite, playerPos));

			if (m_timeSinceLastShot > m_fireRate && alive == true)
			{
				m_timeSinceLastShot = 0;

				if (m_turretOneHealth > 0)
				{
					Projectile *bulletT1 = new Projectile(m_turretOneSprite.getPosition(), m_turretOneSprite.getRotation() + 90, 4, 15, 1500, &m_bulletTexture, m_window);
					bullets.push_back(bulletT1);
					shootingSound->play();
				}
				if (m_turretTwoHealth > 0)
				{
					Projectile *bulletT2 = new Projectile(m_turretTwoSprite.getPosition(), m_turretTwoSprite.getRotation() + 90, 4, 15, 1500, &m_bulletTexture, m_window);
					bullets.push_back(bulletT2);
					shootingSound->play();
				}
				if (m_turretThreeHealth > 0)
				{
					Projectile *bulletT3 = new Projectile(m_turretThreeSprite.getPosition(), m_turretThreeSprite.getRotation() + 90, 4, 15, 1500, &m_bulletTexture, m_window);
					bullets.push_back(bulletT3);
					shootingSound->play();
				}
			}
		}
	default:
		break;
	}

	if (!m_mineType && m_timeSinceLastShot > m_fireRate && alive == true && m_type != BOSS_TYPE)
	{
		m_timeSinceLastShot = 0;
		Projectile *bullet = new Projectile(m_position, m_sprite.getRotation() + 90, 2, 15, 1500, &m_bulletTexture, m_window);
		bullets.push_back(bullet);
		shootingSound->play();
	}

	if (m_timeSinceLastShot > m_fireRate && alive == true)
	{
		m_timeSinceLastShot = 0;
		Projectile *bulletT1 = new Projectile(m_turretOneSprite.getPosition(), m_turretOneSprite.getRotation() + 90, 2, 15, 1500, &m_bulletTexture, m_window);
		Projectile *bulletT2 = new Projectile(m_turretTwoSprite.getPosition(), m_turretTwoSprite.getRotation() + 90, 2, 15, 1500, &m_bulletTexture, m_window);
		Projectile *bulletT3 = new Projectile(m_turretThreeSprite.getPosition(), m_turretThreeSprite.getRotation() + 90, 2, 15, 1500, &m_bulletTexture, m_window);
		shootingSound->play();
		bullets.push_back(bulletT1);
		bullets.push_back(bulletT2);
		bullets.push_back(bulletT3);
	}

	if (m_mineType)
	{
		m_sprite.setRotation(rotator);
	}
}

float Enemy::turretLookAtPlayer(sf::Sprite turret, sf::Vector2f playerPos)
{
	sf::Vector2f curPos = turret.getPosition();
	sf::Vector2f position = playerPos;

	// now we have both the sprite position and the cursor
	// position lets do the calculation so our sprite will
	// face the position of the mouse
	float pi = 3.14159265;

	float dx = curPos.x - position.x;
	float dy = curPos.y - position.y;

	return rotation = ((atan2(dy, dx)) * 180 / PI) + 90;

	//playerStats.m_sprite.setRotation(rotation);
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