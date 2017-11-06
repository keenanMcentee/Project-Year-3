#include "Screen.h"

class Splash : public Screen
{
public:
	Splash(sf::RenderWindow *window);
	void Initialise(GameState *state);
	void Update();
	void Draw(sf::RenderWindow *window);
private:
	
};