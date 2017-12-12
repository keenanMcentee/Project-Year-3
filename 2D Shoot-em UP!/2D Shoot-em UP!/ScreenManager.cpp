#include "ScreenManager.h"
#include <iostream>

/// <summary>
/// creates each of the screen objects and passes them the render window
/// sets the initial gamestate
/// </summary>
/// <param name="window"></param>
ScreenManager::ScreenManager(sf::RenderWindow *window) : m_splash(window), m_license(window), m_mainMenu(window), m_options(window),
m_help(window), m_credits(window), m_play(window, &currentState), m_pause(window)
{
	currentState = GameState::Play;
}

/// <summary>
/// calls the initialise for each of the screens
/// </summary>
void ScreenManager::Initialise()
{
	fromPause = false;
	m_splash.Initialise(&currentState);
	m_license.Initialise(&currentState);
	m_mainMenu.Initialise(&currentState, &fromPause);
	m_options.Initialise(&currentState);
	m_credits.Initialise(&currentState);
	m_pause.Initialise(&currentState, &fromPause);
	m_help.Initialise(&currentState);

}

/// <summary>
/// Switch statement that calls the update of a screen depending on which gamestate is active
/// </summary>
/// <param name="clock"></param>
void ScreenManager::Update(sf::Clock *clock)
{
	dt = clock->restart();
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
		m_help.Update();
		break;
	case GameState::Options:
		m_options.Update(fromPause);
		break;
	case GameState::Pause:
		m_pause.Update();
		break;
	case GameState::Play:
		m_play.Update(dt);
		break;
	case GameState::Credits:
		m_credits.Update();
		break;
	case GameState::QuitScreen:
		break;
	default:
		break;
	}
	
}

/// <summary>
/// Switch statement that calles the gui event handler for each screen depending on which gamestate is active 
/// the event handler listens for all TGUI related events: button presses, slider scrolls etc 
/// </summary>
/// <param name="e"></param>
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
		m_pause.gui.handleEvent(e);
		break;
	case GameState::Play:
		m_play.gui.handleEvent(e);
		m_play.handleEvent(e);
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

/// <summary>
/// Switch statement that calls the draw function of a screen depending on which gamestate is active
/// </summary>
/// <param name="window"></param>
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
		m_help.Draw(window);
		break;
	case GameState::Options:
		m_options.Draw(window);
		break;
	case GameState::Pause:
		m_pause.Draw(window);
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