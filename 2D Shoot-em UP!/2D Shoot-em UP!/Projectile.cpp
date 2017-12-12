#include "Projectile.h"
#include "vector2.h"


Projectile::Projectile(sf::Vector2f position, float _rotation, float _speed, float _damage, float _distance, sf::Texture *texture)
{
	m_position = position;
	m_startPos = m_position;
	m_velocity = sf::Vector2f(cos(_rotation * 3.14 / 180) * _speed, sin(_rotation * 3.14 / 180) * _speed);
	m_damage = _damage;
	m_maxDist = _distance;
	m_alive = true;
	m_sprite.setRotation(_rotation);
	m_sprite.setTexture(*texture);
}

void Projectile::update()
{
	m_position += m_velocity;

	if (std::sqrt(std::powf(m_position.x - m_startPos.x, 2) + std::powf(m_position.y - m_startPos.y, 2)) > m_maxDist)
	{
		m_alive = false;
	}

	m_sprite.setPosition(m_position);
}

void Projectile::draw(sf::RenderWindow *window)
{
	if (m_alive)
		window->draw(m_sprite);
}

bool Projectile::isAlive()
{
	return m_alive;
}

tgui::FloatRect Projectile::getRect()
{
	sf::FloatRect boundingBox = m_sprite.getGlobalBounds();
	return tgui::FloatRect(boundingBox.left, boundingBox.top, boundingBox.width, boundingBox.height);
}
