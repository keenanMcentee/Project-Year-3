#include "Map.h"
#include "Screen.h"
#include "Player.h"
#include "Merchant.h"
#include <math.h>
#include "Enemy.h"
#include <SFGUI\SFGUI.hpp>
#include <SFGUI\Widgets.hpp>
#include <SFML\Graphics.hpp>
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
	Merchant merchant;
	sf::View playerView;
	float distBetween(sf::Vector2f playerPos, sf::Vector2f OtherPos);
	sfg::SFGUI sfgui;
	sfg::Desktop shop;
	bool shopVisible;
	void handleEvent(sf::Event e);
	void closeShop();
};

