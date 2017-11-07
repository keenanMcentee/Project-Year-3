#include "Map.h"
#include "Screen.h"
#include "Player.h"
class Play : public Screen
{
public:
	Play(sf::RenderWindow *window);
	void Update();
	void Draw(sf::RenderWindow *window);

	Map demoMap;
	sf::Texture mapTexture;
	Player player;
	sf::View view;
	sf::Keyboard keyboard;
	sf::Keyboard pastKeyboard;
};

