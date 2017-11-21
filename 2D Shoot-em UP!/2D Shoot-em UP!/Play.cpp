#include "Play.h"


/// <summary>
/// Constructor for the play game.
/// Requires Window for the Screen class which it inherits from.
/// </summary>
/// <param name="window"></param>
Play::Play(sf::RenderWindow *window) : Screen(window)
{
	b2Vec2 gravity(0, 0);
	//box2d->SetGravity(gravity);
	
	mapTexture.loadFromFile("ASSETS/SpriteSheets/DungeonTileSet.png");
	demoMap.initialise("Level1_Tile Layer 1.csv", "Level1_Tile Layer 2.csv", "", "", &mapTexture);
	player.Initialise(box2d);
	playerView.reset(tgui::FloatRect(0.0, 0.0, 200.0, 250.0));
	playerView.setViewport(tgui::FloatRect(0.0, 0.0, 1.0, 1.0));
	playerView.zoom(4.3f);
}
/// <summary>
/// 
/// </summary>
void Play::Update(sf::Time dt)
{
	player.Update(dt, keyboard, &playerView);

	pastKeyboard = keyboard;
}
/// <summary>
/// Function to handle drawing the player.
/// Changes the view to follow the player.
/// </summary>
/// <param name="window"></param>
void Play::Draw(sf::RenderWindow *window)
{
	playerView.setCenter(player.m_position);
	window->setView(playerView);
	demoMap.draw(window, sf::Vector2f(0, 0), true);
	
	

	player.Draw(window);

	window->setView(window->getDefaultView());
}