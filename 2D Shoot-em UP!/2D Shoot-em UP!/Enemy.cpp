#include "Enemy.h"
Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::Initialise(int type)
{
	m_texture.loadFromFile("ASSETS/enemyBallThingie.png");
	
	srand(time(NULL));
	
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
	m_sprite.setScale(0.01f, 0.01f);
	m_position = sf::Vector2f(100, 500);
	m_type = type;
	//m_position = sf::Vector2f(rand() % 700 + 50, rand() % 700 + 50);
	rotator = 0;
	m_sprite.scale(3, 3);
	m_sprite.setPosition(m_position);
	m_speed = 1;

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
	std::cout << m_position.y <<  std::endl;
	m_position.x += m_speed;
				//Height of curve		width of curve		position on screen.
	if (m_type == SASSY_BOY)
	{
		m_position.y = 100 * sin(m_position.x / 100) + 400;
	}
	else if (m_type == CURVY_BOY)
	{
		m_position.y = 100 * sin(m_position.x / 10) + 300;
	}
	m_sprite.setRotation(rotator);
	/*if (m_direction == "Up")
	{
		m_sprite.setRotation(0);
	}

	if (m_direction == "Right")
	{
		m_sprite.setRotation(90);
	}

	if (m_direction == "Down")
	{
		m_sprite.setRotation(180);
	}

	if (m_direction == "Left")
	{
		m_sprite.setRotation(270);
	}*/
}

void Enemy::Draw(sf::RenderWindow *window)
{
	if (alive)
		window->draw(m_sprite);
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
		return tgui::FloatRect(0,0,0,0);
	}
}