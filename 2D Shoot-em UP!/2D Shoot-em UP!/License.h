#include "Screen.h"

class License : public Screen
{
public:
	License(sf::RenderWindow *window);
	void Initialise(GameState *state);
	void Update();
	void Draw(sf::RenderWindow *window);
};

