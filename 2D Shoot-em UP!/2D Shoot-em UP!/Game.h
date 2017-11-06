#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#pragma comment(lib,"thor-d.lib")
#pragma comment(lib,"sfeMovie-d.lib")
#pragma comment(lib,"sfgui-d.lib")
#pragma comment(lib,"sfgui-s-d.lib")
#pragma comment(lib,"tgui-d.lib")
#pragma comment(lib,"tgui-s-d.lib")
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#pragma comment(lib,"thor.lib") 
#pragma comment(lib,"sfeMovie.lib")
#pragma comment(lib,"sfgui.lib")
#pragma comment(lib,"sfgui-s.lib")
#pragma comment(lib,"tgui.lib")
#pragma comment(lib,"tgui-s.lib")
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

/*
###############################################
##@Authors:	Keenan McEntee
##			Keith Wilson
##@DateStart: 04/10/2017
##@Summary: A 2D top down shoot-em up game with some strategic elements.
###############################################
*/

#ifndef GAME
#define GAME
#include <Thor\Animations.hpp>
#include "Box2D\Box2D.h"
#include <SFGUI\SFGUI.hpp>
#include <SFGUI\Widgets.hpp>
#include <SFML\Graphics.hpp>
#include "Map.h"

#ifndef TGUI
#define TGUI
#include <TGUI/TGUI.hpp>
#endif // !TGUI

#include "uiHelper.h"
class Game
{
public:
	Game();
	~Game();
	void Run();
	void Initialise();
	void Update(sf::Clock &clock);
	
	void Draw();
protected:
	sf::RenderWindow m_window;
	sf::Mouse mouse;
	sf::Keyboard keyboard;
	Map testLevel;
	sf::Texture testLevelTexture;
	sfg::SFGUI sfgui;
	sfg::Label::Ptr label;
	sfg::Button::Ptr button;
	sfg::Box::Ptr box;
	sfg::Desktop desktop;


};
#endif // !GAME



