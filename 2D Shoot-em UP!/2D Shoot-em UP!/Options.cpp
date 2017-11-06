#include "Options.h"


Options::Options(sf::RenderWindow *window) : Screen(window)
{
}
void Options::Initialise(GameState *state)
{
	gui.add(uiHelper::makeLabel("OPTIONS SCREEN", sf::Vector2f(100, 100), 32));

	currentState = state;
	tgui::Button::Ptr quitBtn = tgui::Button::create();
	quitBtn->setRenderer(uiHelper::theme.getRenderer("Button"));
	quitBtn->setPosition(600, 400);
	quitBtn->setSize(100, 100);
	quitBtn->setText("Go to Menu");
	quitBtn->connect("pressed", [&]()
	{
		GoToScreen(GameState::MainMenu);
	});
	gui.add(quitBtn, "OptionsQuit_nextBtn");
}
void Options::Update()
{

}
void Options::Draw(sf::RenderWindow *window)
{
	gui.draw();
}