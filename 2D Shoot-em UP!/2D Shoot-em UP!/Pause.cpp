#include "Pause.h"

Pause::Pause(sf::RenderWindow *window) : Screen(window)
{
}

void Pause::Initialise(GameState *state, bool* fromPause)
{
	m_fromPause = fromPause;
	gui.add(uiHelper::makeLabel("PAUSE SCREEN", sf::Vector2f(100, 100), 32));

	currentState = state;

	auto button = uiHelper::makeButton("Return", sf::Vector2f(200, 200), 300, 100);
	button->connect("pressed", [&]() {
		GoToScreen(GameState::Play); 
	});
	gui.add(button, "Pause_retunBtn");

	button = uiHelper::makeButton("Options", sf::Vector2f(200, 600), 300, 100);
	button->connect("pressed", [&]() {
		GoToScreen(GameState::Options);
		*m_fromPause = true;
	});
	gui.add(button, "Menu_optionsBtn");

	button = uiHelper::makeButton("Main Menu", sf::Vector2f(900, 600), 300, 100);
	button->connect("pressed", [&]() {GoToScreen(GameState::MainMenu); });
	gui.add(button, "Pause_mainMenuBtn");

}
void Pause::Update()
{

}
void Pause::Draw(sf::RenderWindow *window)
{
	gui.draw();
}
