#include "Pause.h"

/// <summary>
/// Constructor for the Pause screen.
/// Requires Window for the Screen class which it inherits from.
/// </summary>
/// <param name="window"></param>
Pause::Pause(sf::RenderWindow *window) : Screen(window)
{
}

/// <summary>
/// Initialises the Pause screen and its variables 
/// Creates the Label and Buttons and assigns their functions
/// </summary>
/// <param name="state"></param>
void Pause::Initialise(GameState *state, bool *fromPause)
{
	m_fromPause = fromPause;
	gui.add(uiHelper::makeLabel("PAUSE SCREEN", sf::Vector2f(getScreenSize().x / 6, getScreenSize().y / 15), 32));

	menuBox.loadFromFile("./ASSETS/menu box.png");
	float uiSizeX = getScreenSize().x / 4;
	float uiSizeY = getScreenSize().y / 10;
	m_menuBox.setTexture(menuBox);
	m_menuBox.setPosition(getScreenSize().x / 10, getScreenSize().y / 21);
	m_menuBox.setScale(getScreenSize().x / 720, getScreenSize().y / 720);
	currentState = state;

	auto button = uiHelper::makeButton("Resume", sf::Vector2f(getScreenSize().x / 3 - uiSizeX / 4, getScreenSize().y / 6), uiSizeX, uiSizeY);
	button->connect("pressed", [&]() {
		GoToScreen(GameState::Play); 
	});
	gui.add(button, "Pause_retunBtn");

	button = uiHelper::makeButton("Options", sf::Vector2f(getScreenSize().x / 3 - uiSizeX / 4, getScreenSize().y / 6 * 2.5), uiSizeX, uiSizeY);
	button->connect("pressed", [&]() {
		GoToScreen(GameState::Upgrades);
		*m_fromPause = true;
	});
	gui.add(button, "Menu_optionsBtn");

	button = uiHelper::makeButton("Main Menu", sf::Vector2f(getScreenSize().x / 3 - uiSizeX / 4, getScreenSize().y / 6 * 4), uiSizeX, uiSizeY);
	button->connect("pressed", [&]() {GoToScreen(GameState::MainMenu); });
	gui.add(button, "Pause_mainMenuBtn");

}

void Pause::Update()
{

}

/// <summary>
/// draws the widgets that were added to the gui in the initialise 
/// </summary>
/// <param name="window"></param>
void Pause::Draw(sf::RenderWindow *window)
{
	
	window->draw(m_menuBox);
	gui.draw();
}
