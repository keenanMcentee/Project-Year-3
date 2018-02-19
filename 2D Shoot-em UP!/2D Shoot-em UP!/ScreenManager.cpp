#include "ScreenManager.h"
#include <iostream>

/// <summary>
/// creates each of the screen objects and passes them the render window
/// sets the initial gamestate
/// </summary>
/// <param name="window"></param>
ScreenManager::ScreenManager(sf::RenderWindow *window) : m_splash(window), m_license(window), m_mainMenu(window), m_options(window),
m_help(window), m_credits(window), m_play(window, &m_currentState), m_pause(window), m_postWaveMenu(window), m_upgrades(window)
{
	m_currentState = GameState::Credits;
}

/// <summary>
/// calls the initialise for each of the screens
/// </summary>
void ScreenManager::Initialise()
{
	fromPause = false;
	m_splash.Initialise(&m_currentState);
	m_license.Initialise(&m_currentState);
	m_mainMenu.Initialise(&m_currentState, &fromPause, &m_play);
	m_options.Initialise(&m_currentState);
	m_credits.Initialise(&m_currentState);
	m_pause.Initialise(&m_currentState, &fromPause);
	m_help.Initialise(&m_currentState);
	m_postWaveMenu.Initialise(&m_currentState);
	m_upgrades.Initialise(&m_currentState, &m_play.player.playerStats);
	//menuMusicBuffer.loadFromFile("ASSETS/Sounds/menuMusic.wav");
	menuMusicSound.setBuffer(menuMusicBuffer);
	//gameplayMusicBuffer.loadFromFile("ASSETS/Sounds/gameplayMusic.wav");
	gameplayMusicSound.setBuffer(gameplayMusicBuffer);
	menuMusicSound.setLoop(true);
	gameplayMusicSound.setLoop(true);
}

/// <summary>
/// Switch statement that calls the update of a screen depending on which gamestate is active
/// </summary>
/// <param name="clock"></param>
void ScreenManager::Update(sf::Clock *clock)
{
	if (m_currentState == GameState::Play)
	{
		if (gameplayMusicSound.getStatus() != gameplayMusicSound.Playing)
		{
			menuMusicSound.stop();
			gameplayMusicSound.play();
		}
	}
	else
	{
		if (menuMusicSound.getStatus() != menuMusicSound.Playing)
		{
			gameplayMusicSound.pause();
			menuMusicSound.play();
		}
	}
	dt = clock->restart();
	switch (m_currentState)
	{
	case GameState::Licence:
		m_license.Update();
		break;
	case GameState::Splash:
		m_splash.Update(dt);
		break;
	case GameState::MainMenu:
		m_mainMenu.Update(dt);
		break;
	case GameState::Help:
		m_help.Update(dt);
		break;
	case GameState::Options:
		m_options.Update(fromPause, dt);
		break;
	case GameState::Pause:
		m_pause.Update();
		break;
	case GameState::Play:
		m_play.Update(dt);
		break;
	case GameState::Credits:
		m_credits.Update(dt);
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
	switch (m_currentState)
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
	case GameState::PostWaveMenu:
		m_postWaveMenu.gui.handleEvent(e);
		break;
	case GameState::Upgrades:
		m_upgrades.gui.handleEvent(e);
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
	switch (m_currentState)
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
	case GameState::PostWaveMenu:
		m_postWaveMenu.Draw(window);
		break;
	case GameState::Upgrades:
		m_upgrades.Draw(window, dt);
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