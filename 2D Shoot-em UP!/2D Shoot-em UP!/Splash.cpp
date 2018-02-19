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
	gui.add(uiHelper::makeLabel("ASTROBLAST", sf::Vector2f(100, 100), 64));

	currentState = state;

	auto button = uiHelper::makeButton("Go To Menu", sf::Vector2f(300, 300), 200, 100);
	button->connect("pressed", [&]() {GoToScreen(GameState::MainMenu); });
	gui.add(button, "Splash_nextButton");
}

void Splash::Update(sf::Time dt)
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
void Splash::Draw(sf::RenderWindow *window)
{
	window->draw(backgroundSprite, &menuShader);
	gui.draw();
}
