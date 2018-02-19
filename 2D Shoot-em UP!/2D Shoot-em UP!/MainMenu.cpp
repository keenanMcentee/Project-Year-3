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
void MainMenu::Initialise(GameState *state, bool* fromPause, Play* playScreen)
{
	
	playScreenPtr = playScreen;
	menuBox.loadFromFile("./ASSETS/menu box.png");
	m_menuBox.setTexture(menuBox);
	m_menuBox.setPosition(getScreenSize().x / 10, getScreenSize().y / 21);
	m_menuBox.setScale(getScreenSize().x / 720, getScreenSize().y / 720);
	float uiSizeX = getScreenSize().x / 4;
	float uiSizeY = getScreenSize().y / 10;
	m_fromPause = fromPause;
	gui.add(uiHelper::makeLabel("MAIN MENU SCREEN", sf::Vector2f(getScreenSize().x / 6, getScreenSize().y / 15), 32));

	currentState = state;

	auto button = uiHelper::makeButton("Play", sf::Vector2f(getScreenSize().x /3 - uiSizeX/4, getScreenSize().y / 6), uiSizeX, uiSizeY);
	button->connect("pressed", [&]() {
		
		
		resetButton();
		GoToScreen(GameState::Play);

	});
	gui.add(button, "Menu_playBtn");

	button = uiHelper::makeButton("Options", sf::Vector2f(getScreenSize().x / 3 - uiSizeX / 4, getScreenSize().y / 6 * 2), uiSizeX, uiSizeY);
	button->connect("pressed", [&]() {
		GoToScreen(GameState::Options);
		*m_fromPause = false;
	});
	gui.add(button, "Menu_optionsBtn");
	
	button = uiHelper::makeButton("Credits", sf::Vector2f(getScreenSize().x / 3 - uiSizeX / 4, getScreenSize().y / 6 * 3), uiSizeX, uiSizeY);
	button->connect("pressed", [&]() {GoToScreen(GameState::Credits); });
	gui.add(button, "Menu_creditsBtn");

	button = uiHelper::makeButton("Help", sf::Vector2f(getScreenSize().x / 3 - uiSizeX / 4, getScreenSize().y / 6 * 4), uiSizeX, uiSizeY);
	button->connect("pressed", [&]() {GoToScreen(GameState::Help); });
	gui.add(button, "Menu_helpBtn");

	button = uiHelper::makeButton("Quit", sf::Vector2f(getScreenSize().x / 3 - uiSizeX / 4, getScreenSize().y / 6 * 5), uiSizeX, uiSizeY);
	button->connect("pressed", [&]() {windowPtr->close(); });
	gui.add(button, "Menu_quitBtn");


	
}
void MainMenu::Update(sf::Time dt)
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
void MainMenu::Draw(sf::RenderWindow *window)
{
	window->draw(backgroundSprite, &menuShader);
	window->draw(m_menuBox);
	gui.draw();
}
void MainMenu::resetButton()
{
	playScreenPtr->enemyArray.clear();
	playScreenPtr->player.reset();
	playScreenPtr->enemyCount = 0;
	playScreenPtr->deadEnemies = 0;
	playScreenPtr->bossSpawnCount = 100;
	playScreenPtr->enemySpeed = 0;
}