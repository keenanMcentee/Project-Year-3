#include "License.h"

License::License(sf::RenderWindow *window) : Screen(window)
{

}

void License::Initialise(GameState *state)
{
	gui.add(uiHelper::makeLabel("LICENSE SCREEN", sf::Vector2f(100, 100), 32));

	currentState = state;

	auto button = uiHelper::makeButton("Go To Splash", sf::Vector2f(500, 300), 300, 100);
	button->connect("pressed", [&]() {GoToScreen(GameState::Splash); });
	gui.add(button, "License_SplashBtn");
}

void License::Update()
{

}
void License::Draw(sf::RenderWindow *window)
{
	gui.draw();
}