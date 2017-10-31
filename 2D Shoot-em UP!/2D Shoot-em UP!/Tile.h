#ifndef TILE
#define TILE
#include <SFML/Graphics.hpp>
class Tile
{
public:
	Tile(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position);
	~Tile();
	void draw(sf::RenderWindow *window);
	sf::Sprite m_sprite;
	
protected:
	
};

#endif // !Tile



