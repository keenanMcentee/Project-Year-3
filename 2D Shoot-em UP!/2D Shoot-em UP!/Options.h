#pragma once
#include "Screen.h"
class Options : public Screen
{
public:
public:
	Options(sf::RenderWindow *window);
	void Initialise(GameState *state);
	void Update(bool fromPause, sf::Time dt);
	void Draw(sf::RenderWindow *window);
	void sliderVolumeHandler();
	void chkFullScreenHandler();
	void backBtnHandler(bool fromPause);
	bool fullScreen;
	bool fromPause;

	sf::Texture menuBox;
	sf::Sprite m_menuBox;
private:

};

