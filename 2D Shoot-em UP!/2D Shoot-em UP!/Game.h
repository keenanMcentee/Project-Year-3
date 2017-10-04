/*
###############################################
##@Authors:	Keenan McEntee
##@DateStart: 04/10/2017
##@Summary: A 2D top down shoot-em up game with some strategic elements.
###############################################
*/

#ifndef GAME
#define GAME
	
#include <SFML\Graphics.hpp>
class Game
{
public:
	Game();
	~Game();
	void Run();
	void Initialise();
	void Update();
	void Draw();
protected:
	sf::RenderWindow m_window;
};
#endif // !GAME



