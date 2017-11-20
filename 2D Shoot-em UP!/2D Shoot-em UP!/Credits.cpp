#include "Credits.h"


Credits::Credits(sf::RenderWindow *window) : Screen(window)
{
}
void Credits::Initialise(GameState *state)
{
	gui.add(uiHelper::makeLabel("CREDITS SCREEN", sf::Vector2f(100, 100), 32));

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
	gui.add(quitBtn, "CreditsQuit_nextBtn");
}
void Credits::Update()
{

}
void Credits::Draw(sf::RenderWindow *window)
{
	gui.draw();
}