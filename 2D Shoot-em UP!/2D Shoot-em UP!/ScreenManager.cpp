#include "ScreenManager.h"
#include <iostream>
ScreenManager::ScreenManager(sf::RenderWindow *window) : m_splash(window), m_license(window), m_mainMenu(window), m_options(window),
m_help(window), m_credits(window), m_play(window)
{
	currentState = GameState::Licence;
}
void ScreenManager::Initialise()
{
	m_splash.Initialise(&currentState);
	m_license.Initialise(&currentState);
	m_mainMenu.Initialise(&currentState);
	m_options.Initialise(&currentState);
	m_credits.Initialise(&currentState);
}
void ScreenManager::Update(sf::Clock *clock)
{
	switch (currentState)
	{
	case GameState::Licence:
		m_license.Update();
		break;
	case GameState::Splash:
		m_splash.Update();
		break;
	case GameState::MainMenu:
		m_mainMenu.Update();
		break;
	case GameState::Help:
		std::cout << "CURRENT SCREEN IS HELP" << std::endl;
		m_help.Update();
		break;
	case GameState::Options:
		m_options.Update();
		break;
	case GameState::Pause:
		break;
	case GameState::Play:
		m_play.Update();
		break;
	case GameState::Credits:
		std::cout << "CURRENT SCREEN IS CREDITS" << std::endl;
		m_credits.Update();
		break;
	case GameState::QuitScreen:
		break;
	default:
		break;
	}
}
void ScreenManager::handleEvent(sf::Event e)
{
	switch (currentState)
	{
	case GameState::Licence:
		m_license.gui.handleEvent(e);
		break;
	case GameState::Splash:
		m_splash.gui.handleEvent(e);
		break;
	case GameState::MainMenu:
		m_mainMenu.gui.handleEvent(e);
		break;
	case GameState::Help:
		m_help.gui.handleEvent(e);
		break;
	case GameState::Options:
		m_options.gui.handleEvent(e);
		break;
	case GameState::Pause:
		//.gui.handleEvent(e);
		break;
	case GameState::Play:
		m_play.gui.handleEvent(e);
		break;
	case GameState::Credits:
		m_credits.gui.handleEvent(e);
		break;
	case GameState::QuitScreen:
		m_mainMenu.gui.handleEvent(e);
		break;
	default:
		break;
	}
}
void ScreenManager::Draw(sf::RenderWindow *window)
{
	switch (currentState)
	{
	case GameState::Licence:
		m_license.Draw(window);
		break;
	case GameState::Splash:
		m_splash.Draw(window);
		break;
	case GameState::MainMenu:
		m_mainMenu.Draw(window);
		break;
	case GameState::Help:
		break;
	case GameState::Options:
		m_options.Draw(window);
		break;
	case GameState::Pause:
		break;
	case GameState::Play:
		m_play.Draw(window);
		break;
	case GameState::Credits:
		m_credits.Draw(window);
		break;
	case GameState::QuitScreen:
		break;
	default:
		break;
	}
}