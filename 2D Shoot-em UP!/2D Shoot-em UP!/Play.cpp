#include "Play.h"

/// <summary>
/// Constructor for the play game.
/// Requires Window for the Screen class which it inherits from.
/// </summary>
/// <param name="window"></param>
Play::Play(sf::RenderWindow *window, GameState *state) : Screen(window)
{
	mapTexture.loadFromFile("ASSETS/SpriteSheets/RoadDemoSheet.png");
	demoMap.initialise("DemoLevel_Tile Layer 1.csv", "", "", "", &mapTexture);
	player.Initialise();

	currentState = state;
}


/// <summary>
/// 
/// </summary>
void Play::Update()
{
	player.Update(keyboard);

	if (keyboard.isKeyPressed(keyboard.Escape))
	{
		GoToScreen(GameState::Pause);
	}

	pastKeyboard = keyboard;
}
/// <summary>
/// 
/// </summary>
/// <param name="window"></param>
void Play::Draw(sf::RenderWindow *window)
{
	demoMap.draw(window, sf::Vector2f(0, 0), true);
	player.Draw(window);

	window->setView(window->getDefaultView());
}