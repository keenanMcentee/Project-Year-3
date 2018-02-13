#include "Help.h"

/// <summary>
/// Constructor for the help screen.
/// Requires Window for the Screen class which it inherits from.
/// </summary>
/// <param name="window"></param>
Help::Help(sf::RenderWindow *window) : Screen(window)
{
}

/// <summary>
/// Initialises the help screen and its variables 
/// Creates the Label and Buttons and assigns their functions
/// </summary>
/// <param name="state"></param>
void Help::Initialise(GameState *state)
{
	gui.add(uiHelper::makeLabel("HELP SCREEN", sf::Vector2f(100, 100), 32));

	currentState = state;

	auto button = uiHelper::makeButton("Back", sf::Vector2f(900, 600), 300, 100);
	button->connect("pressed", [&]() {GoToScreen(GameState::MainMenu); });
	gui.add(button, "Menu_playBtn");
}
void Help::Update(sf::Time dt)
{
	float time = dt.asSeconds();
	timeSinceStart += dt.asSeconds();
	menuShader.setUniform("time", timeSinceStart);
	menuShader.setUniform("resolution", sf::Glsl::Vec2(windowPtr->getSize().x, windowPtr->getSize().y));
}

/// <summary>
/// draws the widgets that were added to the gui in the initialise 
/// </summary>
/// <param name="window"></param>
void Help::Draw(sf::RenderWindow *window)
{
	window->draw(backgroundSprite, &menuShader);
	gui.draw();
}