#include "Screen.h"

/// <summary>
/// screen constructor
/// creates a screen with a render window
/// </summary>
/// <param name="window"></param>
Screen::Screen(sf::RenderWindow *window)
{
	gui.setTarget(*window);
	windowPtr = window;
	screenSize = sf::Vector2f(window->getSize().x,window->getSize().y);

	blankTexture.loadFromFile("./ASSETS/blankTexture.png");
	backgroundSprite.setTexture(blankTexture);
	backgroundSprite.setScale(3, 3);
	backgroundShader.loadFromFile("./ASSETS/shaders/fragmentShaders/ground_one.frag", sf::Shader::Fragment);
	menuShader.loadFromFile("./ASSETS/shaders/fragmentShaders/menu.frag", sf::Shader::Fragment);
}

/// <summary>
/// Sets the current gamestate to the passed gamestate
/// </summary>
/// <param name="state"></param>
void Screen::GoToScreen(GameState state)
{
	*currentState = state;
}
sf::Vector2f Screen::getScreenSize()
{
	return screenSize;
}