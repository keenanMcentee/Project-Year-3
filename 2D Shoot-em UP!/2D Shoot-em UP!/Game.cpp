#include "Game.h"

Game::Game() : m_window(sf::VideoMode(1280,720), "2D Shoot-em Up!", sf::Style::Default), m_screenManager(&m_window)
{
	m_window.setFramerateLimit(60);
	//gui.setTarget(m_window);
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
	sf::Event event;
	sf::Clock clock;
	while (m_window.isOpen()) {
		// Event processing.
		while (m_window.pollEvent(event)) {
			//gui.handleEvent(event);
			m_screenManager.handleEvent(event);
		}
		Update(clock);
		Draw();

	}
}
/// <summary>
/// Function to Initialise all elements of the game.
/// </summary>
void Game::Initialise()
{
	m_screenManager.Initialise();
	
}
/// <summary>
/// Function that handles updating all objects and elements of the game.
/// </summary>
void Game::Update(sf::Clock &clock)
{
	m_screenManager.Update(&clock);
}
/// <summary>
/// Function that communicates with the window to output everything to screen.
/// </summary>
void Game::Draw()
{
	m_window.clear(sf::Color::Black);
	m_screenManager.Draw(&m_window);
	//gui.draw();
	m_window.display();
}