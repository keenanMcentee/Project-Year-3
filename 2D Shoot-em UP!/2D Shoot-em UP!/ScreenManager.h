#include "GameStates.h"
#include "License.h"
#include "Splash.h"
#include "MainMenu.h"
#include "options.h"
#include "Credits.h"
#include "Help.h"
#include "Play.h"
#include "TGUI\TGUI.hpp"
#ifndef SCREENMANAGER
#define	SCREENMANGER

class ScreenManager
{
public:
	ScreenManager(sf::RenderWindow *window);
	void Update(sf::Clock *clock);
	void Draw(sf::RenderWindow *window);
	void Initialise();
	void handleEvent(sf::Event e);
private:
	Splash m_splash;
	License m_license;
	MainMenu m_mainMenu;
	Options m_options;
	Help m_help;
	Credits m_credits;
	Play m_play;
	GameState currentState;
	sf::Time lastFrame;
	sf::Time dt;
};
#endif // !SCREENMANAGER
