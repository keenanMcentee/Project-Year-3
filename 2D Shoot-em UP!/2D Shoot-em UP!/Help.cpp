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
	float uiSizeX = getScreenSize().x / 20;
	float uiSizeY = getScreenSize().y / 20;
	menuBox.loadFromFile("./ASSETS/menu box.png");
	m_menuBox.setTexture(menuBox);
	m_menuBox.setPosition(60, 30);
	m_menuBox.setScale(1.4, 0.8);
	gui.add(uiHelper::makeLabel("HELP SCREEN", sf::Vector2f(150, 40), 25));
	gui.add(uiHelper::makeLabel("W: Move up\nA: Move Left \nS: Move Down\nD: Move Right", sf::Vector2f(150, 170), 25));
	gui.add(uiHelper::makeLabel("Left Click to shoot\nLeft Shift for speed Boost!", sf::Vector2f(300, 390), 25));
	currentState = state;

	auto button = uiHelper::makeButton("Back", sf::Vector2f(getScreenSize().x / 12 * 10 - uiSizeX / 4, (getScreenSize().y / 6) * 5.5), uiSizeX * 2, uiSizeY);
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
	window->draw(m_menuBox);
	gui.draw();
}