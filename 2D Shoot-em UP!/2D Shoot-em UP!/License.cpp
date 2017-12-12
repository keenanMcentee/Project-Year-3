#include "License.h"

/// <summary>
/// Constructor for the Licence screen.
/// Requires Window for the Screen class which it inherits from.
/// </summary>
/// <param name="window"></param>
License::License(sf::RenderWindow *window) : Screen(window)
{

}

/// <summary>
/// Initialises the Licence and its current Gamestate 
/// Creates the Label and Button and assigns its function
/// </summary>
/// <param name="state"></param>
void License::Initialise(GameState *state)
{
	gui.add(uiHelper::makeLabel("LICENSE SCREEN", sf::Vector2f(100, 100), 32));

	currentState = state;

	auto button = uiHelper::makeButton("Go To Splash", sf::Vector2f(300, 300), 200, 100);
	button->connect("pressed", [&]() {GoToScreen(GameState::Splash); });
	gui.add(button, "License_SplashBtn");
}

void License::Update()
{

}

/// <summary>
/// draws the widgets that were added to the gui in the initialise 
/// </summary>
/// <param name="window"></param>
void License::Draw(sf::RenderWindow *window)
{
	gui.draw();
}