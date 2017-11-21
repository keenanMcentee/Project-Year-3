#ifndef SCREEN
#define SCREEN
#include <TGUI\TGUI.hpp>
#include "uiHelper.h"
#include "GameStates.h"
class Screen
{
public:
	tgui::Gui gui;
	Screen(sf::RenderWindow *window);
	void GoToScreen(GameState state);
protected:
	GameState *currentState;
	GameState *previousState;
	sf::RenderWindow* windowPtr;
	bool* m_fromPause;
};
#endif // !SCREEN



