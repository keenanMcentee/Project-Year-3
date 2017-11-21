#include "MainMenu.h"




MainMenu::MainMenu(sf::RenderWindow *window) : Screen(window)
{
}

void MainMenu::Initialise(GameState *state, bool* fromPause)
{
	m_fromPause = fromPause;
	gui.add(uiHelper::makeLabel("MAIN MENU SCREEN", sf::Vector2f(100, 100), 32));

	currentState = state;

	auto button = uiHelper::makeButton("Play", sf::Vector2f(200, 200), 300, 100);
	button->connect("pressed", [&]() {GoToScreen(GameState::Play); });
	gui.add(button, "Menu_playBtn");

	button = uiHelper::makeButton("Options", sf::Vector2f(200, 600), 300, 100);
	button->connect("pressed", [&]() {
		GoToScreen(GameState::Options);
		*m_fromPause = false;
	});
	gui.add(button, "Menu_optionsBtn");
	
	button = uiHelper::makeButton("Credits", sf::Vector2f(900, 200), 300, 100);
	button->connect("pressed", [&]() {GoToScreen(GameState::Credits); });
	gui.add(button, "Menu_creditsBtn");

	button = uiHelper::makeButton("Quit", sf::Vector2f(900, 600), 300, 100);
	button->connect("pressed", [&]() {windowPtr->close(); });
	gui.add(button, "Menu_quitBtn");

}
void MainMenu::Update()
{

}
void MainMenu::Draw(sf::RenderWindow *window)
{
	gui.draw();
}