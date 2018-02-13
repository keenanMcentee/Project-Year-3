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
	sf::RenderWindow* m_window;
protected:
	GameState *currentState;
	GameState *previousState;
	sf::RenderWindow* windowPtr;
	bool* m_fromPause;
	sf::Vector2f getScreenSize();
	sf::Texture blankTexture;
	sf::Sprite backgroundSprite;
	sf::Shader backgroundShader;
	sf::Shader menuShader;
	float timeSinceStart;
private:
	sf::Vector2f screenSize;

};
#endif // !SCREEN



