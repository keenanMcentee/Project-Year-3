#include "Play.h"



Play::Play(sf::RenderWindow *window) : Screen(window)
{
	mapTexture.loadFromFile("ASSETS/SpriteSheets/RoadDemoSheet.png");
	demoMap.initialise("DemoLevel_Tile Layer 1.csv", "", "", "", &mapTexture);
	player.Initialise();
}
void Play::Update()
{
	player.Update(keyboard);

	pastKeyboard = keyboard;
}
void Play::Draw(sf::RenderWindow *window)
{
	window->setView(view);

	demoMap.draw(window, sf::Vector2f(0, 0), true);
	player.Draw(window);

	window->setView(window->getDefaultView());
}