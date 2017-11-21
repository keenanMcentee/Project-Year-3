#include "Credits.h"


Credits::Credits(sf::RenderWindow *window) : Screen(window)
{
}
void Credits::Initialise(GameState *state)
{
	gui.add(uiHelper::makeLabel("CREDITS SCREEN", sf::Vector2f(450, 50), 50));

	currentState = state;

	gui.add(uiHelper::makeLabel("Keith Wilson", sf::Vector2f(200, 200), 80), "Credits_keithLbl");
	gui.add(uiHelper::makeLabel("Keenan McEntee", sf::Vector2f(200, 400), 80), "Credits_keenanLbl");
	gui.add(uiHelper::makeLabel("Kieran Clothier", sf::Vector2f(200, 600), 80), "Credits_kieranLbl");

	auto button = uiHelper::makeButton("Back", sf::Vector2f(900, 600), 300, 100);
	button->connect("pressed", [&]() {GoToScreen(GameState::MainMenu); });
	gui.add(button, "Credits_backBtn");
}
void Credits::Update()
{

}
void Credits::Draw(sf::RenderWindow *window)
{
	gui.draw();
}