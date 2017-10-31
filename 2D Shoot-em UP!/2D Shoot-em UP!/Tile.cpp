#include "Tile.h"



Tile::Tile(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position)
{
	m_sprite.setTexture(*texture);
	m_sprite.setTextureRect(textureRect);
	m_sprite.setPosition(position);
}
void Tile::draw(sf::RenderWindow *window)
{
		window->draw(m_sprite);
}

Tile::~Tile()
{

}
