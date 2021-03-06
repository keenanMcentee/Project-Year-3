#include "Credits.h"

/// <summary>
/// Constructor for the Credits screen.
/// Requires Window for the Screen class which it inherits from.
/// </summary>
/// <param name="window"></param>
Credits::Credits(sf::RenderWindow *window) : Screen(window)
{
}

/// <summary>
/// Initialises the Credits and its variables 
/// Creates the Labels and Button and assigns its function
/// </summary>
/// <param name="state"></param>
void Credits::Initialise(GameState *state)
{
	gui.add(uiHelper::makeLabel("CREDITS SCREEN", sf::Vector2f(150, 40), 25));
	menuBox.loadFromFile("./ASSETS/menu box.png");
	m_menuBox.setTexture(menuBox);
	m_menuBox.setPosition(60, 30);
	m_menuBox.setScale(1.4, 0.8);
	currentState = state;

	gui.add(uiHelper::makeLabel("Keith Wilson", sf::Vector2f(100, 200), 40), "Credits_keithLbl");
	gui.add(uiHelper::makeLabel("Keenan McEntee", sf::Vector2f(100, 250), 40), "Credits_keenanLbl");

	auto button = uiHelper::makeButton("Back", sf::Vector2f(500, 600), 200, 100);
	button->connect("pressed", [&]() {GoToScreen(GameState::MainMenu); });
	gui.add(button, "Credits_backBtn");
}
void Credits::Update(sf::Time dt)
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
void Credits::Draw(sf::RenderWindow *window)
{
	window->draw(backgroundSprite, &menuShader);
	window->draw(m_menuBox);
	gui.draw();
}