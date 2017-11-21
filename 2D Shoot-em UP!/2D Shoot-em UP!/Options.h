#pragma once
#include "Screen.h"
class Options : public Screen
{
public:
public:
	Options(sf::RenderWindow *window);
	void Initialise(GameState *state);
	void Update(bool fromPause);
	void Draw(sf::RenderWindow *window);
	void sliderVolumeHandler();
	void chkFullScreenHandler();
	void backBtnHandler(bool fromPause);
	bool fullScreen;
	bool fromPause;
private:

};

