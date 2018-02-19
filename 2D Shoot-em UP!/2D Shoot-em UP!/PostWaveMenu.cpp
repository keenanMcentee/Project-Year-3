#include "PostWaveMenu.h"

PostWaveMenu::PostWaveMenu(sf::RenderWindow *window) : Screen(window)
{
}

void PostWaveMenu::Initialise(GameState *state)
{
	gui.add(uiHelper::makeLabel("Wave Complete", sf::Vector2f(150, 40), 25));
	menuBox.loadFromFile("./ASSETS/menu box.png");
	m_menuBox.setTexture(menuBox);
	m_menuBox.setPosition(60, 30);
	m_menuBox.setScale(1.4, 0.8);
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
	window->draw(backgroundSprite, &menuShader);
	window->draw(m_menuBox);
	gui.draw();
}