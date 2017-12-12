#include "Map.h"
#include "Screen.h"
#include "Player.h"
#include "Enemy.h"
#include <Box2D\Box2D.h>
class Play : public Screen
{
public:
	Play(sf::RenderWindow *window, GameState *state);
	void Update(sf::Time dt);
	void Draw(sf::RenderWindow *window);
	void HandleCollision();
	Map demoMap;
	sf::Texture mapTexture;
	Player player;
	Enemy enemy;
	sf::View view;
	sf::Keyboard keyboard;
	sf::Keyboard pastKeyboard;

	b2World* box2d;

	sf::View playerView;
};

