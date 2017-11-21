#include "MainMenu.h"

/// <summary>
/// Constructor for the Main Menu screen.
/// Requires Window for the Screen class which it inherits from.
/// </summary>
/// <param name="window"></param>
MainMenu::MainMenu(sf::RenderWindow *window) : Screen(window)
{
}

/// <summary>
/// Initialises the main menu and its variables 
/// Creates the Label and Buttons and assigns their functions
/// </summary>
/// <param name="state"></param>
/// <param name="fromPause"></param>
void MainMenu::Initialise(GameState *state, bool* fromPause)
{
	m_fromPause = fromPause;
	gui.add(uiHelper::makeLabel("MAIN MENU SCREEN", sf::Vector2f(100, 100), 32));

	currentState = state;

	auto button = uiHelper::makeButton("Play", sf::Vector2f(100, 220), 300, 100);
	button->connect("pressed", [&]() {GoToScreen(GameState::Play); });
	gui.add(button, "Menu_playBtn");

	button = uiHelper::makeButton("Options", sf::Vector2f(100, 580), 300, 100);
	button->connect("pressed", [&]() {
		GoToScreen(GameState::Options);
		*m_fromPause = false;
	});
	gui.add(button, "Menu_optionsBtn");
	
	button = uiHelper::makeButton("Credits", sf::Vector2f(900, 220), 300, 100);
	button->connect("pressed", [&]() {GoToScreen(GameState::Credits); });
	gui.add(button, "Menu_creditsBtn");

	button = uiHelper::makeButton("Help", sf::Vector2f(500, 400), 300, 100);
	button->connect("pressed", [&]() {GoToScreen(GameState::Help); });
	gui.add(button, "Menu_helpBtn");

	button = uiHelper::makeButton("Quit", sf::Vector2f(900, 580), 300, 100);
	button->connect("pressed", [&]() {windowPtr->close(); });
	gui.add(button, "Menu_quitBtn");

}
void MainMenu::Update()
{

}

/// <summary>
/// draws the widgets that were added to the gui in the initialise 
/// </summary>
/// <param name="window"></param>
void MainMenu::Draw(sf::RenderWindow *window)
{
	gui.draw();
}