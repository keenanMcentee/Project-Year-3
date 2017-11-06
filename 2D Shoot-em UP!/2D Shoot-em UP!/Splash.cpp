#include "Splash.h"


Splash::Splash(sf::RenderWindow *window) : Screen(window)
{
}
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
void Splash::Draw(sf::RenderWindow *window)
{
	gui.draw();
}
