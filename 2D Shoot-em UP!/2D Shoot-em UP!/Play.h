#include "Map.h"
#include "Screen.h"
class Play : public Screen
{
public:
	Play(sf::RenderWindow *window);
	void Update();
	void Draw(sf::RenderWindow *window);

	Map demoMap;
	sf::Texture mapTexture;
};

