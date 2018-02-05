#include "PostWaveMenu.h"

PostWaveMenu::PostWaveMenu(sf::RenderWindow *window) : Screen(window)
{
}

void PostWaveMenu::Initialise(GameState *state)
{
	gui.add(uiHelper::makeLabel("Wave Complete", sf::Vector2f(150, 50), 50));

	currentState = state;
	
	auto btnContinue = uiHelper::makeButton("Continue", sf::Vector2f(250, 200), 200, 100);
	btnContinue->connect("pressed", [&]() {
		GoToScreen(GameState::Play);
	});
	gui.add(btnContinue);
	auto btnUpgrades = uiHelper::makeButton("Upgrades", sf::Vector2f(250, 350), 200, 100);
	btnUpgrades->connect("pressed", [&]() {
		GoToScreen(GameState::Upgrades);
	});

	gui.add(btnUpgrades);
	auto btnMainMenu = uiHelper::makeButton("Main Menu", sf::Vector2f(250, 500), 200, 100);
	btnMainMenu->connect("pressed", [&]() {
		GoToScreen(GameState::MainMenu);
	});
	gui.add(btnMainMenu);
}

void PostWaveMenu::Draw(sf::RenderWindow *window)
{
	gui.draw();
}