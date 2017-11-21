#include "Splash.h"

/// <summary>
/// Constructor for the Splash screen.
/// Requires Window for the Screen class which it inherits from.
/// </summary>
/// <param name="window"></param>
Splash::Splash(sf::RenderWindow *window) : Screen(window)
{
}

/// <summary>
/// Initialises the Splash screen and its current gamestate 
/// Creates the Label and Button and assigns its function
/// </summary>
/// <param name="state"></param>
void Splash::Initialise(GameState *state)
{
	gui.add(uiHelper::makeLabel("SPLASH SCREEN", sf::Vector2f(100, 100), 32));

	currentState = state;

	auto button = uiHelper::makeButton("Go To Menu", sf::Vector2f(500, 300), 300, 100);
	button->connect("pressed", [&]() {GoToScreen(GameState::MainMenu); });
	gui.add(button, "Splash_nextButton");
}

void Splash::Update()
{

}

/// <summary>
/// draws the widgets that were added to the gui in the initialise 
/// </summary>
/// <param name="window"></param>
void Splash::Draw(sf::RenderWindow *window)
{
	gui.draw();
}
