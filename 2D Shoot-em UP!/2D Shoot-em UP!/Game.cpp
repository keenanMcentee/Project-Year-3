#include "Game.h"



Game::Game() : m_window(sf::VideoMode(1280,720), "2D Shoot-em Up!", sf::Style::Default)
{
	m_window.setFramerateLimit(60);
}


Game::~Game()
{
}
/// <summary>
/// Core game loop for our game.
/// </summary>
void Game::Run()
{
	Initialise();
	while (m_window.isOpen())
	{
		Update();
		Draw();
	}
}
/// <summary>
/// Function to Initialise all elements of the game.
/// </summary>
void Game::Initialise()
{
	view.zoom(-2);
	testLevelTexture.loadFromFile("SpriteSheet.png");
	testLevel.initialise("TestLevel_Tile Layer 1.csv", "TestLevel_Tile Layer 2.csv", "", "", &testLevelTexture);
}
/// <summary>
/// Function that handles updating all objects and elements of the game.
/// </summary>
void Game::Update()
{

}
/// <summary>
/// Function that communicates with the window to output everything to screen.
/// </summary>
void Game::Draw()
{
	m_window.clear(sf::Color::Black);
	m_window.setView(view);
	//Draw code here.
	testLevel.draw(&m_window,sf::Vector2f(600,600), false);

	m_window.display();
}