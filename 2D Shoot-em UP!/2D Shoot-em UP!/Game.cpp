#include "Game.h"



Game::Game() : m_window(sf::VideoMode(1920, 1080), "2D Shoot-em Up!", sf::Style::Default)
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

	//Draw code here.

	m_window.display();
}