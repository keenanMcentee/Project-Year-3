#include "MainMenu.h"



MainMenu::MainMenu(sf::RenderWindow *window) : Screen(window)
{
}

void MainMenu::Initialise(GameState *state)
{
	gui.add(uiHelper::makeLabel("MAIN MENU SCREEN", sf::Vector2f(100, 100), 32));

	currentState = state;

	auto button = uiHelper::makeButton("Play", sf::Vector2f(500, 300), 300, 100);
	button->connect("pressed", [&]() {GoToScreen(GameState::Play); });
	gui.add(button, "Menu_playBtn");

	button = uiHelper::makeButton("Quit", sf::Vector2f(500, 500), 300, 100);
	button->connect("pressed", [&]() {GoToScreen(GameState::QuitScreen); });
	gui.add(button, "Menu_quitBtn");

}
void MainMenu::Update()
{

}
void MainMenu::Draw(sf::RenderWindow *window)
{
	gui.draw();
}