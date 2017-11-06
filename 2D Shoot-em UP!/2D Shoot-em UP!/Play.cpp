#include "Play.h"



Play::Play(sf::RenderWindow *window) : Screen(window)
{
	mapTexture.loadFromFile("ASSETS/SpriteSheets/RoadDemoSheet.png");
	demoMap.initialise("DemoLevel_Tile Layer 1.csv", "", "", "", &mapTexture);
}
void Play::Update()
{

}
void Play::Draw(sf::RenderWindow *window)
{
	demoMap.draw(window, sf::Vector2f(0, 0), true);
}